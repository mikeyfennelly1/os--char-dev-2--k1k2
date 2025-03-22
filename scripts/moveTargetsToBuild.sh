#!/bin/bash

#!/bin/bash

# Function to check file extension, number of full stops, and move the file if valid
check_and_move_file() {
    local file="$1"
    local destination_dir="$2"

    # Check if the destination directory exists, if not, create it
    if [ ! -d "$destination_dir" ]; then
        echo "Destination directory does not exist. Creating it."
        mkdir -p "$destination_dir"
    fi

    # Extract the filename from the full path
    local filename=$(basename "$file")

    # Count the number of dots in the filename (excluding the path)
    local dot_count=$(echo "$filename" | grep -o '\.' | wc -l)

    if [ "$dot_count" -ne 1 ]; then
        echo "Error: Filename '$filename' must contain exactly one full stop."
        return 1
    fi

    # Extract the file extension (everything after the last dot)
    local extension="${filename##*.}"

    # Check if the extension is empty (no extension exists)
    if [ -z "$extension" ]; then
        echo "Error: Filename '$filename' does not have an extension."
        return 1
    fi

    # Check if the extension is .o or .ko
    if [ "$extension" = "o" ] || [ "$extension" = "ko" ]; then
        echo "The file has an allowed extension: .$extension"
    else
        echo "Error: Unsupported file extension '.$extension'"
        return 1
    fi

    # Move the file to the destination directory
    mv "$file" "$destination_dir/"
    
    if [ $? -eq 0 ]; then
        echo "File '$filename' moved to '$destination_dir/'"
    else
        echo "Error: Failed to move the file."
        return 1
    fi

    return 0
}

# Function to process all files in a directory
process_directory() {
    local directory="$1"
    local destination_dir="$2"

    # Check if the directory exists
    if [ ! -d "$directory" ]; then
        echo "Error: Directory '$directory' does not exist."
        return 1
    fi

    # Loop through all files in the directory
    for file in "$directory"/*; do
        # Check if it's a file and not a directory
        if [ -f "$file" ]; then
            check_and_move_file "$file" "$destination_dir"
        fi
    done
}

# Example usage: First argument is the source directory, second is the destination directory
process_directory ./ ../build