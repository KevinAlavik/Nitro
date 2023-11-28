from PIL import Image, ImageDraw, ImageFont

# Function to convert bitmap to array
# (Same as before)

def generate_c_array(bitmap_array):
    c_array = "{\n"
    for row in bitmap_array:
        c_array += f"    0b{row:08b},\n"
    c_array += "},\n"
    return c_array

def generate_c_array_from_ttf(font_path, font_size, characters_per_row):
    img = Image.new('1', (8 * characters_per_row, font_size * 16))
    draw = ImageDraw.Draw(img)
    font = ImageFont.truetype(font_path, font_size)

    all_characters_bitmap = {}
    for char in range(256):  # ASCII range from 0 to 255
        character = chr(char)
        draw.text(((char % characters_per_row) * 8, (char // characters_per_row) * font_size), character, font=font, fill=1)
        character_img = img.crop(((char % characters_per_row) * 8, (char // characters_per_row) * font_size, ((char % characters_per_row) + 1) * 8, ((char // characters_per_row) + 1) * font_size))
        character_bitmap = convert_to_bitmap_array(character_img)
        all_characters_bitmap[character] = character_bitmap

    return all_characters_bitmap

def main():
    font_path = input("Enter the font path: ")
    font_size = int(input("Enter the font size: "))
    characters_per_row = int(input("Enter the number of characters per row: "))
    font_name = input("Enter the font name: ")

    all_characters = generate_c_array_from_ttf(font_path, font_size, characters_per_row)

    print(f"uint8_t {font_name}[{len(all_characters)}][16] = {{")
    for char, bitmap_array in all_characters.items():
        c_array = generate_c_array(bitmap_array)
        print(c_array, end='')
    print("};")

if __name__ == "__main__":
    main()
