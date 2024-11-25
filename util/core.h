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

    cv::Mat autoMorph(cv::Mat input, std::string process, cv::Point point = cv::Point(-1, -1))
    {
        cv::Mat result = input.clone();
        cv::Mat elementX = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size(25, 1));
        cv::Mat elementY = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size(1, 19));
        for (int i = 0; i < process.length() - 2; i += 3)
        {
            std::string cmd = process.substr(i, 3);
            int round = cmd.back() - '0';
            cv::Mat element;
            element = cmd[1] == 'x' ? elementX.clone() : elementY.clone();
            if (cmd[0] == '+')
            {
                cv::dilate(result, result, element, point, round);
            }
            else
            {
                cv::erode(result, result, element, point, round);
            }
        }
        return result;
    }

    cv::Mat find(double ratioMin = 2.2, double ratioMax = 4.0)
    {
        std::cout << "find" << std::endl;
        cv::Mat edgeDetected = this->processed.clone();
        // iteratively dilate and erode the image to find an area with relatively high density of edges, which might
        // indicate that it is where the plate located
        cv::Mat processed;
        // cv::Mat elementX = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size(25, 1));
        // cv::Mat elementY = cv::getStructuringElement(cv::MorphShapes::MORPH_RECT, cv::Size(1, 19));
        // cv::Point point(-1, -1);
        // cv::dilate(edgeDetected, processed, elementX, point, 2);
        // cv::erode(processed, processed, elementX, point, 4);
        // cv::dilate(processed, processed, elementX, point, 2);
        // cv::erode(processed, processed, elementY, point, 1);
        // cv::dilate(processed, processed, elementY, point, 2);
        processed = autoMorph(edgeDetected, "+x2-x4+x2-y1+y2");
        this->processed = processed;

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
            std::cout << "r: " << ratio << std::endl;
            if (ratio >= ratioMin && ratio <= ratioMax)
            {
                this->extracted = this->source(rect);
                return this->extracted;
            }
        }
        return processed;
    }

    cv::Mat rectBound(cv::Mat bImage)
    {
        cv::Mat canny;
        cv::Canny(bImage, canny, 500, 200, 3);
        return canny;
    }

    static int getIntValue_SC(cv::Mat mat, int row, int col)
    {
        return mat.at<cv::Vec3i>(row, col)[0];
    }

    static int getMin(cv::Mat mat)
    {
        double result;
        cv::minMaxLoc(mat, &result);
        return std::floor(result);
    }

    static int getMax(cv::Mat mat)
    {
        double result;
        cv::minMaxLoc(mat, NULL, &result);
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
        if (getIntValue_SC(rowHist, 0, 0) > threshold)
        {
            pointUp = 0;
            isPeak = true;
        }
        std::vector<std::vector<int>> wavePeaks;
        for (int i = 0; i < rowHist.rows; i++)
        {
            int value = getIntValue_SC(rowHist, i, 0);
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

    cv::Mat cut(int minThreshold = 20, int minCharWidth = 5)
    {
        if (!this->cutted.empty())
        {
            this->cutted.clear();
        }
        // cut the characters in the plate detected
        auto plateWidth = this->fitted.cols;
        cv::Mat colHist = cv::Mat_<int>(1, plateWidth); // count the white pixel of every column
        for (int col = 0; col < plateWidth; col++)
        {
            int count = cv::countNonZero(this->fitted.colRange(col, col + 1));
            colHist.at<int>(0, col) = count;
        }
        std::vector<int> zeroCol;
        for (int col = 0; col < plateWidth; col++)
        {
            // search for zero columns' index
            if (colHist.at<int>(0, col) == 0)
            {
                zeroCol.emplace_back(col);
            }
        }
        // std::cout << zeroCol.size() << std::endl;
        // std::cout << cv::countNonZero(colHist) << std::endl;
        // std::cout << plateWidth << std::endl;
        // for (auto zero_col : zeroCol)
        // {
        //     std::cout << zero_col << " | ";
        // }
        for (int i = 0; i < zeroCol.size() - 1; i++)
        {
            // std::cout << getIntValue_SC(colHist, 0, i) << " | ";
            auto maxV = getMax(colHist.colRange(zeroCol[i], zeroCol[i + 1] + 1).clone());
            if (zeroCol[i + 1] - zeroCol[i] >= minCharWidth && maxV >= minThreshold)
            {
                this->cutted.emplace_back(this->fitted.colRange(zeroCol[i], zeroCol[i + 1]));
            }
        }
        std::cout << "cut" << this->cutted.size() << std::endl;
        // std::cout << this->cutted[3].type() << std::endl;
        return this->cutted[0];
    }

    cv::Mat recog()
    {
        cv::Mat corner, scaled;
        cv::resize(this->cutted[0].clone(), scaled, cv::Size(), 10, 10);
        cv::cornerHarris(scaled, corner, 2, 3, 0.04);
        std::cout << "scaled:" << scaled.size << std::endl;;
        for (int r = 0; r < corner.rows; r++)
        {
            for (int c = 0; c < corner.cols; c++)
            {
                if (static_cast<int>(corner.at<uchar>(r, c)) > 200)
                {
                    cv::circle(scaled, cv::Point(c, r), 1, cv::Scalar(255, 255, 255), 2, 8, 0);
                }
            }
        }
        std::cout << scaled.type();
        return scaled;
    }

    cv::Mat process()
    {
        edgeDetection();
        // morphProcess();
        // extract();
        find();
        fit();
        // std::cout << recog() << std::endl;
        // return this->extracted;
        cut();
        // recog();
        return this->cutted[0];
    }
};

#endif //CORE_H
