//CS112_A3_Part2-B_SectionNum11_20230727_20231204_20231176.cpp
// This program let user filter any image s/he needs.
/** Author-1 : MennaAllah Osama Mohammad Ali ,, 20231176 ,,S11
 * Author-2 : Rahaf Luai Al-Hakimi ,, 20230727 ,,S11
 * Author-3 : Yasmeen Abd Al-hameed Farag ,, 20231204 ,,S11
 */
/* Rahaf did :   Filter 1-4-7-10-13
 * Menna did :   Filter 2-5-8-11-16
 * Yasmeen did : Filter 3-6-9-12-17
 */
// Diagram functions link : https://drive.google.com/file/d/1GgzzPQOugKsXdi1zCfUpTF9sTAHmNCRW/view?usp=sharing

//GitHub task : https://github.com/MennaAllah-Osama/SP

#include <iostream>
#include <fstream>
#include "Image_Class.h"
#include <cmath>
#include <vector>

using namespace std;

bool checkFile(const string &filename) {
    ifstream file(filename.c_str());
    return file.good();
}
string name;
string getFileName() {

    while (true) {

        cout << "Please enter the file name of your NEW photo:" << endl;
        cin >> name;


        if (!checkFile(name)) {
            cout << "Image file does not exist. Please try again." << endl;
            continue;
        }
        break;
    }
    return name;
}
void getSavedFilename(Image&image) {
    string filename;
    while (true) {
        cout << "Do you want to save the image in (1)_same file name (2)_New file name  : "<< endl;
        int choice;
        cin >> choice;
        if (choice == 1) {
            image.saveImage(name);
            cout << " image saved successfully with the same filename." << endl;
            break;
        }
        else if  (choice == 2) {
            // Save the image with a new filename
            cout << "Enter the filename to save the filtered photo: " << endl;
            string new_file_name;
            cin >> new_file_name;
            size_t pos = new_file_name.find_last_of(".");
            if (pos == string::npos) {
                cout << "Invalid image format. Supported formats are .jpg, .bmp, .jpeg, .png." << endl;
                continue;
            }
            string extension = new_file_name.substr(pos);
            if (!(extension == ".jpg" || extension == ".bmp" || extension == ".jpeg" || extension == ".png")) {
                cout << "Invalid image format. Supported formats are .jpg, .bmp, .jpeg, .png." << endl;
                continue;
            }
            image.saveImage(new_file_name);
            cout << "Fitered image saved successfully in the new filename." << endl;
            break;
        }
    }
}

void filter1(Image&image){
    cout << "Welcome to Grayscale Conversion filter" << endl;
    // Process the image to calculate average color intensity for each pixel
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            // Calculate the average color intensity for each pixel
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;

            // Set each (Red, Green, Blue) component of the pixel to the calculated average
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = avg;
            }
        }
    }cout << "Thanks for using"<< endl ;
}
void filter2(Image&image){
    cout << "Welcome to B&W filter\nThanks for using it" << endl;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg = avg / 3;
            for (int k = 0; k < 3; ++k) {
                if (avg > 128)
                    image(i, j, k) = 255;
                else
                    image(i, j, k) = 0;
            }
        }
    }
}
void filter3(Image&image){
    cout<<"welcome to our program"<<endl;
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Invert the color of each RGB channel for each pixel
                // by subtracting the current pixel value from 255
                image.setPixel(i, j, k, 255 - image.getPixel(i, j, k));
            }
        }
    }
}
Image filter4(Image&image){
    cout << "Welcome to Merge Images filter" << endl;
    string filename2;
    while (true) {
        // Prompt the user to enter the filename of the second image
        cout << "Enter the filename of the second image: "<<endl ;
        cin >> filename2;
        // Check if the second image file exists
        if (!checkFile(filename2)) {
            cout << "Image file " << filename2 << " does not exist. Please try again." << endl;
            continue; // Return to the beginning of the loop to prompt the user again
        }
        break; // Break out of the loop if the filename is valid
    }
    // Load the second image
    Image image2(filename2);
    int new_width, new_height;
    // Prompt the user to enter the new width and height
    cout << "Enter new width and height: "<<endl ;
    cin >> new_width >> new_height;

    // Resize the first image
    Image resized_image1(new_width, new_height);
    for (int new_y = 0; new_y < new_height; ++new_y) {
        for (int new_x = 0; new_x < new_width; ++new_x) {
            int old_x = (new_x * image.width) / new_width;
            int old_y = (new_y * image.height) / new_height;

            for (int c = 0; c < image.channels; ++c) {
                resized_image1(new_x, new_y, c) = image(old_x, old_y, c);
            }
        }
    }

    // Resize the second image
    Image resized_image2(new_width, new_height);
    for (int new_y = 0; new_y < new_height; ++new_y) {
        for (int new_x = 0; new_x < new_width; ++new_x) {
            int old_x = (new_x * image2.width) / new_width;
            int old_y = (new_y * image2.height) / new_height;

            for (int c = 0; c < image2.channels; ++c) {
                resized_image2(new_x, new_y, c) = image2(old_x, old_y, c);
            }
        }
    }

    // Determine the dimensions of the merged image
    int merged_width = new_width;
    int merged_height = new_height;

    // Create a new image to hold the merged result
    Image merged_image(merged_width, merged_height);

    // Merge the two images pixel by pixel
    for (int y = 0; y < merged_height; ++y) {
        for (int x = 0; x < merged_width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                unsigned char value = (resized_image1(x, y, c) + resized_image2(x, y, c)) / 2;
                merged_image(x, y, c) = value;
            }
        }
    }
    return merged_image;
}
void filter5(Image&image){
    cout << "Welcome to flip filter" << endl;
    while (true) {
        cout << "Do you need to\n1-Flip Horizontal\n2-Flip Vertical\n3-Both\n4-exit" << endl;
        int choice0;
        cin >> choice0;
        if (choice0 == 1) {
            for (int i = 0; i < image.width/2 ; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        unsigned temp = 0;
                        temp = image(i, j, k);
                        image.setPixel(i, j, k, image.getPixel(image.width - i - 1, j, k));
                        image.setPixel(image.width - i - 1, j, k, temp);
                    }
                }
            }
            break;
        } else if (choice0 == 2) {
            for (int i = 0; i < image.width ; ++i) {
                for (int j = 0; j < image.height/2; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        unsigned temp = 0;
                        temp = image(i, j, k);
                        image.setPixel(i, j, k, image.getPixel(i, image.height - j - 1, k));
                        image.setPixel(i, image.height - j - 1, k, temp);
                    }
                }
            }
            break;
        } else if (choice0 == 3) {
            for (int i = 0; i < image.width/2 ; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        unsigned temp = 0;
                        temp = image(i, j, k);
                        image.setPixel(i, j, k, image.getPixel(image.width - i - 1, j, k));
                        image.setPixel(image.width - i - 1, j, k, temp);
                    }
                }
            }
            for (int i = 0; i < image.width ; ++i) {
                for (int j = 0; j < image.height/2; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        unsigned temp = 0;
                        temp = image(i, j, k);
                        image.setPixel(i, j, k, image.getPixel(i, image.height - j - 1, k));
                        image.setPixel(i, image.height - j - 1, k, temp);
                    }
                }
            }
            break;
        } else if (choice0 == 4) {
            cout << "GOOD BYE.";
            break;
        } else {
            cout << "Please Enter a valid input" << endl;
            continue;
        }
    }
}
Image filter6(Image&image){
    cout<<"welcome to our program"<<endl;
    // create an image object for the rotated image with swapped width and height
    Image rotated_image(image.height,image.width);
    // ask the user to enter the rotation degree
    cout << "Enter the rotation degree (90, 180, or 270): ";
    int degree;
    cin >> degree;

    // perform rotation based on the selected degree
    switch (degree) {
        case 90: {
            // rotate the image by 90 degrees clockwise
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        // Swap the pixel coordinates for rotation
                        rotated_image(image.height - 1 - j, i, k) = image(i, j, k);
                    }
                }
            }
            break;
        }
        case 180: {
            // rotate the image by 180 degrees clockwise
            for (int i = 0; i < image.width / 2; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        // Swap the pixels
                        unsigned temp = image(i, j, k);
                        image.setPixel(i, j, k, image.getPixel(image.width - i - 1, j, k));
                        image.setPixel(image.width - i - 1, j, k, temp);
                    }
                }
            }
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height / 2; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        // Swap the pixels vertically
                        unsigned temp = image(i, j, k);
                        image.setPixel(i, j, k, image.getPixel(i, image.height - j - 1, k));
                        image.setPixel(i, image.height - j - 1, k, temp);
                    }
                }
            }
            rotated_image= image;
            break;
        }
        case 270: {
            // rotate the image by 270 degrees clockwise
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        // swap the pixel coordinates for rotation
                        rotated_image(j, image.width - 1 - i, k) = image(i, j, k);
                    }
                }
            }
            break;
        }
        default:
            cout << "Invalid choice. Please enter 90, 180, or 270." << endl;
    }
    return rotated_image;
}
void filter7(Image& image) {
    cout << "Welcome to Darken and Lighten Image filter" << endl;
    char choice;
    bool validChoice;

    do {
        validChoice = true;

        cout << "Do you want to darken or lighten the image? Enter 'd' for darken or 'l' for lighten: ";
        cin >> choice;

        bool darken = (choice == 'd');
        bool lighten = (choice == 'l');

        if (darken || lighten) {
            for (int y = 0; y < image.height; ++y) {
                for (int x = 0; x < image.width; ++x) {
                    for (int c = 0; c < image.channels; ++c) {
                        int color = 0;
                        if (darken) {
                            color = static_cast<int>(image(x, y, c) * 0.5);  // Darken
                        } else if (lighten) {
                            color = static_cast<int>(image(x, y, c) * 1.5);  // Lighten
                        }
                        image(x, y, c) = min(255, color);
                    }
                }
            }
        } else {
            cout << "Please enter 'd' or 'l' only. Try again." << endl;
            validChoice = false;
        }
    } while (!validChoice);
}
Image filter8(Image& image) {
    cout << "Welcome to crop filter" << endl;
    long long x, y, New_width, New_height;
    while (true) {
        // Check if the cropped area is within the image bounds
        cout << "Enter the x-coordinate of the upper-left corner: " << endl;
        cin >> x;
        if (x < 0 || x > image.width) {
            cout<< "Error !!!" <<endl ;
            continue;
        }
        cout << "Enter the y-coordinate of the upper-left corner: " << endl;
        cin >> y;
        if (y < 0 || y > image.height) {
            cout<< "Error !!!" <<endl ;
            continue;
        }
        cout << "Enter the New_width of the cropped area: " << endl;
        cin >> New_width;
        if (New_width <= 0 || x + New_width > image.width){
            cout<< "Invalid cropping dimensions!"<< endl;
            continue;
        }
        cout << "Enter the New_height of the cropped area: " << endl;
        cin >> New_height;
        if (New_height <= 0 ||y + New_height > image.height){
            cout<< "Invalid cropping dimensions!"<< endl;
            continue;
        }
        break;
    }
    Image cropped_image(New_width, New_height);
    for (int i = 0; i < New_width; ++i) {
        for (int j = 0; j < New_height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                cropped_image.setPixel(j, i, k, image.getPixel(x + j, y + i, k));
            }
        }
    }cout << "Thanks for using"<< endl ;
    return cropped_image;
}
void filter9(Image& image)
{
    cout<<"welcome to our program"<<endl;
    // Prompt the user to enter the type of frame and the color of the frame.
    int choice_1, choice_2;
    while (true) {
        cout << "Enter the type of the frame 1_simple or 2_fancy): ";
        cin >> choice_1;
        cout << "Enter the color of the frame (1_black\n 2_white\n 3_red\n 4_green\n 5_blue): "<<endl;
        cin >> choice_2;
        if ((choice_1 == 1 || choice_1 == 2) &&
            (choice_2 ==  1|| choice_2 == 2 || choice_2 == 3 ||
             choice_2 == 4 || choice_2 == 5)) {
            break;
        } else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
    // Apply the selected frame based on the user's choices
    if (choice_1 == 1 && choice_2 == 1) {
        // Apply simple black frame.
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = 0;
                    }
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 1 && choice_2 == 2) {
        // Apply simple white frame.
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = 255;
                    }
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 1 && choice_2 == 3) {
        // Apply simple red frame
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    image(i, j, 0) = 255;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 0;
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 1 && choice_2 == 4) {
        // Apply simple green frame.
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 255;
                    image(i, j, 2) = 0;
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 1&& choice_2 == 5) {
        // Apply simple blue frame
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 255;
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 2 && choice_2 == 1) {
        // Apply fancy black frame
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if ((i >= 60 && i <= 70) || (j >= 60 && j <= 70) ||
                    (i >= image.width - 70 && i <= image.width - 60) ||
                    (j >= image.height - 70 && j <= image.height - 60)) {
                    image(i, j, 0) = 150;
                    image(i, j, 1) = 150;
                    image(i, j, 2) = 0;
                } else if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = 0;
                    }
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 2 && choice_2 == 2) {
        // Apply fancy white frame.
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if ((i >= 60 && i <= 70) || (j >= 60 && j <= 70) ||
                    (i >= image.width - 70 && i <= image.width - 60) ||
                    (j >= image.height - 70 && j <= image.height - 60)) {
                    image(i, j, 0) = 100;
                    image(i, j, 1) = 100;
                    image(i, j, 2) = 0;
                } else if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = 255;
                    }
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 2 && choice_2 == 3) {
        // Apply fancy red frame.
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if ((i >= 60 && i <= 70) || (j >= 60 && j <= 70) ||
                    (i >= image.width - 70 && i <= image.width - 60) ||
                    (j >= image.height - 70 && j <= image.height - 60)) {
                    image(i, j, 0) = 150;
                    image(i, j, 1) = 150;
                    image(i, j, 2) = 0;
                } else if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    image(i, j, 0) = 255;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 0;
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 2 && choice_2 == 4) {
        // Apply fancy green frame.
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if ((i >= 60 && i <= 70) || (j >= 60 && j <= 70) ||
                    (i >= image.width - 70 && i <= image.width - 60) ||
                    (j >= image.height - 70 && j <= image.height - 60)) {
                    image(i, j, 0) = 150;
                    image(i, j, 1) = 150;
                    image(i, j, 2) = 0;
                } else if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 255;
                    image(i, j, 2) = 0;

                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    } else if (choice_1 == 2 && choice_2 == 5) {
        // Apply fancy blue frame.
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                if ((i >= 60 && i <= 70) || (j >= 60 && j <= 70) ||
                    (i >= image.width - 70 && i <= image.width - 60) ||
                    (j >= image.height - 70 && j <= image.height - 60)) {
                    image(i, j, 0) = 150;
                    image(i, j, 1) = 150;
                    image(i, j, 2) = 0;
                } else if (i < 40 || i >= image.width - 40 || j < 40 || j >= image.height - 40) {
                    image(i, j, 0) = 0;
                    image(i, j, 1) = 0;
                    image(i, j, 2) = 255;
                } else {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k);
                    }
                }
            }
        }
    }
}
Image filter10(Image &image) {
    cout << "Welcome to Detect Image Edges filter" << endl;
    // Fixed threshold value for edge detection
    const int threshold_Value = 50;

    // Process the image to calculate average color intensity for each pixel
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;

            // Calculate the average color intensity for each pixel
            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;

            // Set all color components of the pixel to the calculated average
            for (int k = 0; k < 3; ++k) {
                image(i, j, k) = avg;
            }
        }
    }

    // Create a new Image to store the edge-detected image
    Image edgeImage(image.width, image.height);

    // Process the image to detect edges
    for (int i = 1; i < image.width - 1; ++i) {
        for (int j = 1; j < image.height - 1; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                // Calculate differences with neighboring pixels
                int diff_x = image(i + 1, j, k) - image(i - 1, j, k);
                int diff_y = image(i, j + 1, k) - image(i, j - 1, k);

                // Compute magnitude of gradient
                int gradient_magnitude = sqrt(diff_x * diff_x + diff_y * diff_y);

                // Threshold gradient magnitude to detect edges using fixed threshold value
                if (gradient_magnitude > threshold_Value) {
                    // Edge detected
                    edgeImage(i, j, k) = 0; // Set edge pixel to white
                } else {
                    // Not an edge
                    edgeImage(i, j, k) = 255; // Set non-edge pixel to black
                }
            }
        }
    }
    return edgeImage;
}
Image filter11(Image& image) {
    cout << "Welcome to Resize filter" << endl;
    int new_width, new_height;
    double ratio;

    // Let the user choose between entering new dimensions or a ratio
    int choice;
    cout << "Enter (1) to specify new dimensions or (2) to specify a reduction/increase ratio: " << endl;
    cin >> choice;

    if (choice == 1) {
        // User chooses new dimensions
        cout << "Enter new width and height: " << endl;
        cin >> new_width;
        cin >> new_height;
    } else if (choice == 2) {
        // User chooses reduction/increase ratio
        cout << "Enter reduction/increase ratio (e.g., 0.5 for 50% reduction, 2 for doubling the size): " << endl;
        cin >> ratio;

        // Calculate new dimensions based on the ratio
        new_width = round(image.width * ratio);
        new_height = round(image.height * ratio);
    }

    // Create an Image with the provided file name and new dimensions
    Image image1(new_width, new_height);

    // Process the image with the new width and height
    for (int new_i = 0; new_i < new_width; ++new_i) {
        for (int new_j = 0; new_j < new_height; ++new_j) {
            int i = (new_i * image.width) / new_width;
            int j = (new_j * image.height) / new_height;

            for (int k = 0; k < image.channels; ++k) {
                image1(new_i, new_j, k) = image(i, j, k);
            }
        }
    }cout <<"Thanks for using"<< endl ;
    return image1;
}
void filter12(Image& image){
    cout<<"welcome to our program"<<endl;
    // create a 2D prefix sum array to store cumulative sums for each channel
    vector<vector<vector<int>>> prefixSum(3, vector<vector<int>>(image.width + 1, vector<int>(image.height + 1, 0)));
    // compute the cumulative sums for each channel
    for (int k = 0; k < 3; ++k) { // Iterate over color channels (RGB)
        for (int i = 1; i <= image.width; ++i) {
            for (int j = 1; j <= image.height; ++j) {
                // compute the prefix sum using dynamic programming
                prefixSum[k][i][j] = image(i - 1, j - 1, k) +
                                     prefixSum[k][i - 1][j] +
                                     prefixSum[k][i][j - 1] -
                                     prefixSum[k][i - 1][j - 1];
            }
        }
    }

    // define kernel size
    int kernel = 35;
    int radius = kernel / 2; // radius is half the size of the kernel
//iterate over width and height
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < 3; ++k) { // iterate over color channels (RGB)
                // compute the coordinates of the kernel bounds
                int x1 = max(0, i - radius);
                int y1 = max(0, j - radius);
                int x2 = min(image.width, i + radius + 1);
                int y2 = min(image.height, j + radius + 1);

                // compute the sum of pixel values within the kernel using prefix sums
                int sum = prefixSum[k][x2][y2] - prefixSum[k][x2][y1] - prefixSum[k][x1][y2] + prefixSum[k][x1][y1];

                // compute the average pixel value
                image(i, j, k) = sum / (min(kernel, x2 - x1) * min(kernel, y2 - y1));
            }
        }
    }
}
void filter13(Image& image){
    cout << "Welcome to natural sunlight filter" << endl;

    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            for (int c = 0; c < image.channels; c++) {
                if ( c == 2 ){
                    unsigned char& pixelValue =image.getPixel(x, y, c);
                    pixelValue *= 0.8; // Reduce yellow light by 30%
                }
            }
        }
    }
}
void filter16(Image& image){
    cout << "Welcome to Purple filter\nThanks for using it" << endl;
    for (int i = 0; i < image.width ; ++i) {
        for (int j = 0;j < image.height; ++j) {
            unsigned char& Red = image(i, j, 0);
            unsigned char& Green = image(i, j , 1);
            unsigned char& Blue = image(i, j , 2);

            Green *= 0.69;
        }
    }
}
void filter17(Image& image){
    cout<<"welcome to our program"<<endl;
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            int red = 245; // Get the red channel value
            int green = 255 - image.getPixel(i, j, 2); // Invert the green channel value
            int blue = 255 - image.getPixel(i, j, 1); // Invert the blue channel value

            // Set the pixel values in the  image
            image.setPixel(i, j, 0, red); // Set the red channel
            image.setPixel(i, j, 1, green); // Set the green channel
            image.setPixel(i, j, 2, blue); // Set the blue channel
        }
    }
}


int main() {
    string name;
    Image image;
    int choice ;
    cout << "Welcome to our photoshop program."<<endl;
    while (true){
        cout << "Do you need to 1)Save the last image or 2)NOT " <<endl;
        cin >> choice ;
        if (choice ==1 ){
            getSavedFilename(image) ;
            name=getFileName();
            image.loadNewImage(name);
            break;
        }else if (choice==2){
            name=getFileName();
            image.loadNewImage(name);
            break;
        }
    }

    while (true){

        cout <<"Which filter do you need to apply ?"<<endl;
        cout <<"1: Grayscale Conversion      2: Black and White      3: Invert Image\n4: Merge Images              5: Flip Image           6: Rotate Image\n7: Darken and Lighten Image  8: Crop Images          9: Adding a Frame to the Picture\n10: Detect Image Edges       11: Resizing Images     12: Blur Images\n13: Natural Sunlight         14: Purple Effect       15: Infrared Photography\n16: Save       17: Exit" <<endl;
        cin >>choice ;
        if (choice==1){
            filter1(image);
        } else if (choice==2){
            filter2(image);
        } else if (choice==3){
            filter3(image);
        } else if (choice==4){
            image=filter4(image);
        } else if (choice==5){
            filter5(image);
        }else if (choice==6){
            image= filter6(image);
        }else if (choice==7){
            filter7(image);
        }else if (choice==8){
            image=filter8(image);
        }else if (choice==9){
            filter9(image);
        }else if (choice==10){
            image=filter10(image);
        }else if (choice==11){
            image=filter11(image);
        }else if (choice==12){
            filter12(image);
        }else if (choice==13){
            filter13(image);
        }else if (choice==14){
            filter16(image);
        }else if (choice==15){
            filter17(image);
        }
        else if (choice==16){
            getSavedFilename(image) ;
        }
        else if (choice==17){
            cout << "Do you need to 1)save before closing or 2)NOT ??  "<<endl;
            int choice ;
            cin >> choice ;
            if (choice==1 ){
                getSavedFilename(image) ;
                cout <<"Good Bye ya user ya 7abiby."<<endl;
                break;
            }else if (choice==2){
                cout <<"Good Bye ya user ya 7abiby."<<endl;
                break;}
        }else {
            cout << "INVALID CHOICE !!!!" << endl;
            continue;
        }
    }
    return 0;
}