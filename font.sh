#!/bin/bash

# Check if font file path is provided
if [ $# -eq 0 ]; then
    echo "Please provide the path to the font file."
    exit 1
fi

font_path="$1"
output_filename="kfont.psf.gz"
extracted_dir="temp"
extracted_filename="kfont.psf"

# Create a temporary directory for extracting the font
mkdir -p "$extracted_dir"

# Extract the font to the temporary directory
cp "$font_path" "$extracted_dir/"
cd "$extracted_dir" || exit
gunzip -f "$output_filename"

# Check if the extracted font is PSF version 2
file_type=$(file -b "$extracted_filename")
if [[ "$file_type" != *"PC Screen Font"* ]]; then
    echo "The provided file is not a PSF font file (version 2)."
    cd ..
    rm -rf "$extracted_dir"
    exit 1
fi

# Move the font back to the original directory with the desired name
mv "$extracted_filename" "../$output_filename"

# Clean up the temporary directory
cd ..
rm -rf "$extracted_dir"

echo "Font processing completed. Saved as $output_filename."
