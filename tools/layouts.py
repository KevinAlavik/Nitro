import keyboard

def generate_c_array(layout_code):
    print(f"// {layout_code} layout")
    print("struct KeyState", layout_code.lower() + "_layout[0xFF + 1] = {")
    
    layout = keyboard.KeyboardLayout.from_name(layout_code)
    for i in range(0xFF + 1):
        if i in layout.key_to_scan_codes:
            key_info = layout.key_to_scan_codes[i][0]
            normal = key_info.normal[0] if key_info.normal else ""
            shifted = key_info.shifted[0] if key_info.shifted else ""
            caps = key_info.caps[0] if key_info.caps else ""
            print(f"\t[0x{i:02X}] = {{ '{normal}', '{shifted}', '{caps}' }},")
        else:
            print(f"\t[0x{i:02X}] = {{ '', '', '' }},")
    
    print("};")

# Get layout code from user input
layout_code = input("Enter keyboard layout code (e.g., SE-SV): ")
generate_c_array(layout_code)
