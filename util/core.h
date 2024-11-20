//
// Created by Dekki on 24-11-15.
//

#ifndef CORE_H
#define CORE_H

#include <qimage.h>
#include <string>
#include <vector>
#include <opencv4/opencv2/core/mat.hpp>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>

class Core
{
public:
    cv::Mat source, processed, marked, extracted, fitted;
    std::vector<cv::Mat> cutted;

    Core() {};

    QImage mat2QImage(const cv::Mat mat)
    {
        QImage output;
        const uchar* source;
        switch (mat.type())
        {
        case CV_8UC1:
            output = QImage(mat.cols, mat.rows, QImage::Format_Indexed8);
            output.setColorCount(256);
            for (int i = 0; i < 256; i++)
            {
                output.setColor(i, qRgb(i, i, i));
            }
            source = mat.data;
            for (int row = 0; row < mat.rows; row++)
            {
                uchar* dest = output.scanLine(row);
                memcpy(dest, source, mat.cols);
                source += mat.step;
            }
            return output;
        case CV_8UC3:
            source = static_cast<const uchar*>(mat.data);
            output = QImage(source, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
            return output.rgbSwapped();
        default:
            return {};
        }
    }

    cv::Mat readImage(std::string path)
    {
        this->source = cv::imread(path, cv::IMREAD_COLOR);
        return source;
    }

    cv::Mat edgeDetection()
    {
        cv::Mat image = this->source.clone();
        cv::Mat grayImage;
        cv::cvtColor(image, grayImage, cv::COLOR_RGB2GRAY);
        cv::Mat blurred, sobelX, sobelY, canny;
        cv::medianBlur(grayImage, blurred, 3);
        float mask[3][3] = {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}
        };
        cv::Mat maskY = cv::Mat(3, 3, CV_32F, mask) / 8;
        cv::Mat maskX = maskY.t();
        cv::filter2D(blurred, sobelX, CV_32F, maskX);
        cv::filter2D(blurred, sobelY, CV_32F, maskY);
        sobelX = cv::abs(sobelX);
        sobelY = cv::abs(sobelY);
        cv::Canny(blurred, canny, 250, 100, 3);
        this->processed = canny.clone();
        return canny;
    }

    cv::Mat morphProcess()
    {
        cv::Mat edgeDetected = this->processed.clone();
        // iteratively dilate and erode the image to find an area with relatively high density of edges, which might
        // indicate that it is where the plate located
        cv::Mat processed;
        cv::Mat elementX = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size(25, 1));
        cv::Mat elementY = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size(1, 19));
        cv::Point point(-1, -1);
        cv::dilate(edgeDetected, processed, elementX, point, 2);
        cv::erode(processed, processed, elementX, point, 4);
        cv::dilate(processed, processed, elementX, point, 2);
        cv::erode(processed, processed, elementY, point, 1);
        cv::dilate(processed, processed, elementY, point, 2);
        this->processed = processed;
        return processed;
    }

    cv::Mat extract(double ratioMin = 2.2, double ratioMax = 4.0)
    {
        cv::Mat blurred;
        cv::Mat temp = this->processed.clone();
        cv::Mat contourImage = source.clone();
        cv::medianBlur(temp, blurred, 15);
        cv::medianBlur(blurred, blurred, 15);
        std::vector<std::vector<cv::Point>> contourPoints;
        cv::findContours(temp, contourPoints, cv::RetrievalModes::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        cv::drawContours(contourImage, contourPoints, -1, {255, 0, 255}, 3);
        this->marked = contourImage;
        std::vector<cv::Point> rectPoints;
        for (const auto & contourPoint : contourPoints)
        {
            cv::Rect rect = cv::boundingRect(cv::Mat(contourPoint));
            auto ratio = (float)rect.width / (float)rect.height;
            if (ratio >= ratioMin && ratio <= ratioMax)
            {
                this->extracted = this->source(rect);
                return this->extracted;
            }
        }
        return this->marked;
    }

    cv::Mat rectBound(cv::Mat bImage)
    {
        cv::Mat canny;
        cv::Canny(bImage, canny, 500, 200, 3);
        return canny;
    }

    static int getValue_SC(cv::Mat mat, int row, int col)
    {
        return mat.at<cv::Vec3i>(row, col)[0];
    }

    static int getMin(cv::Mat mat, int start = 0, int end = -1)
    {
        double result;
        if (mat.rows == 1)
        {
            if (end == -1) end = mat.cols;
            cv::minMaxLoc(mat.colRange(start, end).clone(), &result);
        }
        else
        {
            if (end == -1) end = mat.rows;
            cv::minMaxLoc(mat.rowRange(start, end).clone(), &result);
        }
        return std::floor(result);
    }

    static int getMax(cv::Mat mat, int start = 0, int end = -1)
    {
        double result;
        if (mat.rows == 1)
        {
            if (end == -1) end = mat.cols;
            cv::minMaxLoc(mat.colRange(start, end).clone(), NULL, &result);
        }
        else
        {
            if (end == -1) end = mat.rows;
            cv::minMaxLoc(mat.rowRange(start, end).clone(), NULL, &result);
        }
        return std::floor(result);
    }

    cv::Mat fit(int topMargin = 0, int bottomMargin = 3)
    {
        // fit the plate area more precisely
        cv::Mat plateArea = this->extracted.clone();
        cv::Mat grayPlate;
        cv::cvtColor(plateArea, grayPlate, cv::COLOR_RGB2GRAY);
        cv::Mat plateBinary;
        cv::threshold(grayPlate, plateBinary, 50, 255, cv::THRESH_OTSU);
        cv::Mat rowHist; // row histogram calculates the sums of all rows, size: (r, 1)
        cv::reduce(plateBinary, rowHist, 1, cv::ReduceTypes::REDUCE_SUM, CV_32SC1);
        double histMin = getMin(rowHist);  // minimum of the histogram
        double histAvg = cv::mean(rowHist)[0]; // average of the histogram
        double threshold = (histMin + histAvg) / 2;
        // finding the peaks of the waves from the histogram
        int pointUp = -1;
        bool isPeak = false;
        if (getValue_SC(rowHist, 0, 0) > threshold)
        {
            pointUp = 0;
            isPeak = true;
        }
        std::vector<std::vector<int>> wavePeaks;
        for (int i = 0; i < rowHist.rows; i++)
        {
            int value = getValue_SC(rowHist, i, 0);
            if (isPeak && value < threshold)
            {
                if (i - pointUp > 2)
                {
                    isPeak = false;
                    wavePeaks.emplace_back(std::vector{pointUp, i});
                }
            }
            else if (!isPeak && value >= threshold)
            {
                isPeak = true;
                pointUp = i;
            }
            if (isPeak && pointUp != -1 && i - pointUp > 4)
            {
                wavePeaks.emplace_back(std::vector{pointUp, i});
            }
        }
        // pick the furthest wave peak
        int span = 0;
        std::vector<int> selected;
        for (const auto & wavePeak : wavePeaks)
        {
            int currentSpan = wavePeak[1] - wavePeak[0];
            if (currentSpan > span)
            {
                span = currentSpan;
                selected = wavePeak;
            }
        }
        int rowStart = std::max(0, selected[0] - topMargin);
        int rowEnd = std::min(selected[1] + bottomMargin + 1, plateBinary.rows);
        auto fitted = plateBinary.rowRange(rowStart, rowEnd);
        this->fitted = fitted.clone();
        return fitted;
    }

    cv::Mat cut(int lowerThreshold = 10)
    {
        // cut the characters in the plate detected
        // TODO: bug?????!!!!!!!!!
        auto plateWidth = this->fitted.cols;
        auto plateHeight = this->fitted.rows;
        cv::Mat colHist;
        cv::reduce(this->fitted, colHist, 0, cv::ReduceTypes::REDUCE_SUM, CV_32SC1);
        colHist = colHist * (-1);
        int start = 0, end = -1;
        for (int col = 0; col < plateWidth; col++)
        {
            if (this->cutted.size() >= 7)
            {
                break;
            }
            cv::Mat temp;
            auto whitePixelCount = getValue_SC(colHist, 0, col);
            if (whitePixelCount == 0)
            {
                if (col - start >= plateWidth * (1 / 8) && getMin(colHist) < -lowerThreshold)
                {
                    end = col;
                    this->cutted.emplace_back(this->fitted.rowRange(start, end).clone());
                    start = col + 1;
                }
                else
                {
                    end = -1;
                }
            }
        }
        return this->cutted[0];
    }

    cv::Mat process()
    {
        edgeDetection();
        morphProcess();
        extract();
        fit();
        // std::cout << recog() << std::endl;
        // return this->extracted;
        return cut();
    }
};

#endif //CORE_H
