#!/bin/bash

# Set the directory path
font_dir="/usr/share/consolefonts"

# Create a directory to store the PSF files
output_dir="fonts"
mkdir -p "$output_dir"

# Variables for counting PSF v2 files
total_files=0
psf2_files=0

# Loop through gzipped files in the consolefonts directory
for file in "$font_dir"/*.gz; do
    # Use zcat to extract the file without creating a temporary file
    zcat "$file" > temp_font_file

    # Run 'file' command to check if it's a PSF v2 file
    file_type=$(file temp_font_file)

    # Print debug information
    echo "File: $file"
    echo "File type: $file_type"

    # Check if it's a PSF v2 file
    if [[ $file_type == *"Linux/i386 PC Screen Font v2 data"* ]]; then
        # Extract the filename from the path
        filename=$(basename "$file" .gz)

        # Save the PSF v2 file to the output directory
        cp temp_font_file "$output_dir/$filename"
        
        # Increment the counter for PSF v2 files
        ((psf2_files++))
    else
        # Delete non-PSF v2 files
        rm temp_font_file
    fi

    # Increment the total files counter
    ((total_files++))
done

# Display the results
echo "Processed $total_files files. Found $psf2_files PSF v2 files."

# Clean up temporary files
rm -f temp_font_file
