# Computer and Processor Information C++ Program

## Description

This C++ program is designed to retrieve and display specific information about the system it runs on. The main features of the program include:

1. **Retrieve Computer Name**: The program uses the `GetComputerNameExA` function to obtain the computer's NetBIOS name.

2. **Dynamic Memory Allocation**: It allocates memory dynamically to store the computer name. If memory allocation fails, it logs an error message to `sysError.txt`.

3. **Retrieve Processor Information**: The program uses the `GetSystemInfo` function to gather details about the processor, including its architecture and type.

4. **Output Information**: The program writes the computer name and processor details to a file named `sysInfo.txt`. 

5. **Error Handling**: Any issues with memory allocation are recorded in `sysError.txt`.

## Files Generated

- **`sysInfo.txt`**: Contains the computer name and processor information.
- **`sysError.txt`**: Contains an error message if memory allocation fails.

## TODO:

1. **Retrieve Installed Memory** : Implement the `GetPhysicallyInstalledSystemMemory` function.
2. **Get Timezone Information** : Implement `GetTimeZoneInformation` function in the `timezoneapi.h`.

## Usage

- **Build**: Compile the program using a compatible C++ compiler with Windows API support.
- **Run**: Execute the compiled program to generate the output files.

This program is intended for use on Windows systems due to its reliance on Windows-specific API functions.
