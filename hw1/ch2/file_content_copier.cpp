#include <iostream>

using namespace std;

/**
 * @brief
 * Check if the file path is existed in runtime.
 * @param file_path
 * @return true: file exists.
 * @return false: file not exists.
 */
bool isFileAccesableAt(const char *&file_path) {
    FILE *file_ptr = fopen(file_path, "r");
    const bool isExist = !(file_ptr == nullptr);
    fclose(file_ptr);
    return isExist;
}

/**
 * @brief
 * Copy all contents from a file to another file.
 * If new file is already have content, old content will be overwite by new content.
 * @param srcPath source file path
 * @param destPath destination file path
 */
void copyFileContent(const char *&srcPath, const char *&destPath) {
    // Check if the source file is existed.
    const bool isSourceFileExists = isFileAccesableAt(srcPath);
    if (!isSourceFileExists) {
        perror("Source file can't be accessed: ");
        exit(1);
    }

    // Check if the destination file is existed.
    const bool isDestinationFileExists = isFileAccesableAt(destPath);
    if (!isDestinationFileExists) {
        perror("Destination file can't be accessed: ");
        exit(1);
    }

    // Get pointers for both files.
    FILE *src_ptr = fopen(srcPath, "r");
    FILE *dest_ptr = fopen(destPath, "w");

    // Copy the contents of a file character by character to another file.
    int content_buf;
    while ((content_buf = fgetc(src_ptr)) != EOF) {
        fputc(content_buf, dest_ptr);
    }

    fclose(src_ptr);
    fclose(dest_ptr);

    cout << "Content copied (overwite)." << endl;
}

int main(int argc, char const *argv[]) {
    // Check if source file and destination file path are provided by the user.
    if (argc < 3) {
        if (argc == 1) {
            cout << "A File content copy & overwite program." << endl;
            cout << "Copyright (C) 2022 Xanonymous" << endl;
            cout << "\nUsage: " << argv[0] << " [SOURCE_FILE_PATH] [DESTINATION_FILE_PATH]" << endl;
            return 0;
        }

        cout << "File path not provided!" << endl;
        cout << "Please provide two existed file paths for copy operation," << endl;
        cout << "For example: ./copy a.txt b.txt" << endl;
        return 1;
    }

    // Get the provided file paths.
    const char *&sourceFilePath = argv[1];
    const char *&destinationFilePath = argv[2];

    // Copy file content.
    copyFileContent(sourceFilePath, destinationFilePath);

    return 0;
}
