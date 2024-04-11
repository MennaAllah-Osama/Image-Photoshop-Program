//CS112_A3_Part1_SectionNum11_20230727_20231204_20231176.cpp
// This program let user filter any image s/he needs (GRAY SCALE , B&W , FLIP IMAGE , DARKEN&LIGHTEN , INVERT IMAGE )
/** Author-1 : MennaAllah Osama Mohammad Ali ,, 20231176 ,,S11
 * Author-2 : Rahaf Luai Al-Hakimi ,, 20230727 ,,S11
 * Author-3 : Yasmeen Abd Al-hameed Farag ,, 20231204 ,,S11
 */
/*Menna did : Black and White & flip  (Filter 2-5)
 * Rahaf did : Grayscale Conversion & Darken and Lighten   (Filter 1-7)
 * Yasmeen did : Invert Image (Filter 3)
 */


#include <fstream>
#include "Image_Class.h"
#include <iostream>

using namespace std;
bool checkFile(const string& filename) {
    ifstream file(filename.c_str());
    return file.good();
}
int main() {
    while (true) {
        int choice;
        cout << "Welcome in our program." << endl;
        cout
                << "1-Grayscale Conversion\n2-Black and White\n3-Darken and Lighten Image\n4-Flip Image\n5-Invert Image\n6-Exit"
                << endl;
        cin >> choice;
        if (choice == 1) {
            string name;

            // Prompt the user to enter the file name of the photo
            cout << "Please enter the file name of the photo:" << endl;
            cin >> name;

            // Check if the image file exists
            if (!checkFile(name)) {
                cout << "Image file does not exist. Please try again." << endl;
                continue; // Return to the beginning of the loop to prompt the user again
            }

            // Create an Image object and load the image with the given file name
            Image image(name);

            // If the image is loaded successfully, proceed
            if (image.loadNewImage(name)) {
                cout << "Loaded successfully" << endl;
            } else {
                cout << "Failed to load the image." << endl;
                continue; // Return to the beginning of the loop to prompt the user again
            }

            // Loop through each pixel in the image
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
            }

            string filename;
            cout << "Enter the filename of the image: ";
            cin >> filename;

            // Save the modified image with the provided file name
            int x = image.saveImage(filename);
            cout << "Image saved with return code: " << x << endl;


        } else if (choice == 2) {
            while (true) {
                int choice0;
                cout << "Do you need \n1-Black&White filter\n2-Exit" << endl;
                cin >> choice0;
                if (choice0 == 1) {
                    string file_name;
                    string new_file_name;

                    // Prompt the user to enter the file name of the image
                    cout << "Enter file name of your image : " << endl;
                    cin >> file_name;

                    // Check if the image file exists
                    if (!checkFile(file_name)) {
                        cout << "Image file does not exist. Please try again." << endl;
                        continue; // Restart the loop to prompt for another file name
                    }

                    // Create an Image object with the provided file name
                    Image image(file_name);

                    // Iterate through each pixel in the image and apply black and white filter
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

                    // Prompt the user to enter a new file name to save the modified image
                    cout << "Enter a new file name to save your image on it : " << endl;
                    cin >> new_file_name;

                    // Save the modified image with the provided file name
                    image.saveImage(new_file_name);
                    int x = image.saveImage(new_file_name);
                    if (x == 1) {
                        cout << "Saved successfully." << endl;
                    } else {
                        cout << "Failed to save your image!!!" << endl;
                    }
                } else if (choice0 == 2) {
                    cout << "GOOD BYE." << endl;
                    break;
                } else {
                    cout << "INVALID INPUT!!!" << endl;
                    continue;
                }
            }


        } else if (choice == 3) {
            // Prompt the user to enter the file name of the photo
            cout << "Please enter the file name of the photo:" << endl;
            string name;
            cin >> name;

            // If the image file exists, proceed
            if (checkFile(name)) {
                // Create an Image object with the provided file name
                Image image(name);

                // If the image is loaded successfully, proceed
                if (image.loadNewImage(name)) {
                    cout << "Loaded successfully" << endl;

                    char choice;
                    bool validChoice;

                    // Repeat until a valid choice is entered
                    do {
                        validChoice = true;

                        // Prompt the user to choose whether to darken or lighten the image
                        cout << "Do you want to darken or lighten the image? Enter 'd' for darken or 'l' for lighten: ";
                        cin >> choice;

                        // Determine if the user chose to darken or lighten the image
                        bool darken = (choice == 'd');
                        bool lighten = (choice == 'l');

                        // Iterate through each pixel in the image
                        for (int y = 0; y < image.height; ++y) {
                            for (int x = 0; x < image.width; ++x) {
                                for (int c = 0; c < image.channels; ++c) {
                                    int color = 0;
                                    // Darken the pixel if chosen by the user
                                    if (darken) {
                                        color = static_cast<int>(image(x, y, c) * 0.5);  // Darken
                                    }
                                        // Lighten the pixel if chosen by the user
                                    else if (lighten) {
                                        color = static_cast<int>(image(x, y, c) * 1.5);  // Lighten
                                    } else {
                                        // If an invalid choice is entered, prompt the user to try again
                                        cout << "Please enter 'd' or 'l' only. Try again." << endl;
                                        validChoice = false; // Set the flag to false to prompt re-entry
                                        break;
                                    }
                                    // Ensure the color value stays within valid range
                                    image(x, y, c) = min(255, color);
                                }
                                if (!validChoice) {
                                    break;
                                }
                            }
                            if (!validChoice) {
                                break;
                            }
                        }

                        // If a valid choice was made, proceed to save the image
                        if (validChoice) {
                            string filename;
                            cout << "Enter the filename of the image: ";
                            cin >> filename;

                            // Save the modified image with the provided file name
                            int x = image.saveImage(filename);
                            cout << "Image saved with return code: " << x << endl;
                        }
                    } while (!validChoice); // Continue looping until a valid choice is entered
                } else {
                    cout << "Failed to load the image." << endl;
                }
            } else {
                cout << "Image file does not exist. Please try again." << endl;
            }


        } else if (choice == 4) {
            string file_name;
            string new_file_name;
            cout << "Enter file name of your image : " << endl;
            cin >> file_name;

            // Check if the input file exists
            if (!checkFile(file_name)) {
                cout << "Image file does not exist. Please try again." << endl;
                continue; // Go back to the beginning of the loop to prompt for the file name again
            }

            Image image(file_name);

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
                } else if (choice0 == 4) {
                    cout << "GOOD BYE.";
                    break;
                } else {
                    cout << "Please Enter a valid input" << endl;
                    continue;
                }

                cout << "enter a new file name to save your image on it : " << endl;
                cin >> new_file_name;
                image.saveImage(new_file_name);
                int x = image.saveImage(new_file_name);
                if (x == 1) {
                    cout << "saved succesfully." << endl;
                } else {
                    cout << "cannot save your image!!!" << endl;
                }
            }
        }
        else if (choice == 5) {
            while (true) {
                try {
                    // Clear the input buffer
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Ask the user to enter the file name
                    cout << "Enter the file name: ";
                    string f_name;
                    getline(cin, f_name);

                    // Check if the image file exists
                    if (!checkFile(f_name)) {
                        cout << "Image file does not exist. Please try again." << endl;
                        continue; // Prompt the user to input another file name
                    }

                    // Load the image using the provided file name
                    Image image(f_name);

                    // Check if the image was loaded successfully
                    if (!image.loadNewImage(f_name)) {
                        // If the image failed to load, throw an exception
                        throw runtime_error("Could not open or find the image");
                    }

                    // Iterate over each pixel in the image to invert colors
                    for (int i = 0; i < image.width; ++i) {
                        for (int j = 0; j < image.height; ++j) {
                            for (int k = 0; k < 3; ++k) {
                                // Invert the color of each RGB channel for each pixel
                                // by subtracting the current pixel value from 255
                                image.setPixel(i, j, k, 255 - image.getPixel(i, j, k));
                            }
                        }
                    }

                    // Prompt the user to enter the new file name to save the modified image
                    string new_file;
                    cout << "Enter the new file name: ";
                    cin >> new_file;

                    // Save the modified image with the provided file name
                    int save_result = image.saveImage(new_file);
                    if (save_result == 1) {
                        cout << "Image modified and saved as " << new_file << endl;
                    } else {
                        cout << "Failed to save the image." << endl;
                    }
                    break; // Exit the while loop after processing the image
                } catch (const exception &e) {
                    // If an exception occurs during image processing or saving, catch it here
                    // and print an error message
                    cout << "Error: " << e.what() << endl;
                    // Prompt the user to input another file name
                    cout << "Please input another file name." << endl;
                }
            }


        } else if (choice == 6) {
            cout << "GOOD BYE." << endl;
            break;
        } else {
            cout << "INVALID INPUT !!!!!!" << endl;
            continue;
        }
    }
    return 0;
}
