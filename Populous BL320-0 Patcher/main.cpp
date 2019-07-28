/*
Populous The Beginning Raw File Patcher
Brandan Tyler Lasley 2019 (7/25/2019)
*/
#include <iostream>
#include <fstream>
#include <memory>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        std::cout << argv[1] << " <---- " << argv[2];
    }
    else
    {
        std::cout << "Usage: <destnation> <source> \n";
        return -1;
    }

    std::string dest = argv[1];
    std::string source = argv[2];

    //auto spr = Sprite(source);

    // Patch Image
    char            *curr;
    uint8_t         clr, rclr;

    auto hot_patch_raw_image = [&clr, &rclr, &curr](char* raw_file, std::ios::pos_type file_len)
    {
        // Most of this code is just to scan the sprites X, Y locations and checking the byte
        // if its the color we want to replace. If it is we replace it in the j = 1 loop below.

        // This is also how you can draw sprites.
        for (curr = raw_file; curr < (raw_file + static_cast<size_t>(file_len)); curr++)
        {
            clr = *curr;

            // BLUE
            if (clr >= 216 && clr <= 223) // Blues pal color codes
            {
                rclr = clr - 76;
                (*curr) = rclr; // Change pal color to this new pal color.
            }

            // RED
            if (clr >= 240 && clr <= 247) // Reds pal color codes
            {
                rclr = clr - 32;
                (*curr) = rclr; // Change pal color to this new pal color.
            }

            // YELLOW
            if (clr >= 232 && clr <= 239) // Yellows pal color codes
            {
                rclr = clr - 72;
                (*curr) = rclr; // Change pal color to this new pal color.
            }

            // GREEN 
            if (clr >= 224 && clr <= 231) // Greens pal color codes
            {
                rclr = clr - 92;
                (*curr) = rclr; // Change pal color to this new pal color.
            }
        }
    };

    char* raw_file = nullptr;
    std::ios::pos_type raw_size;

    // Load Raw
    {
        std::ifstream reader(source, std::ios::binary | std::ios::ate);

        if (reader.is_open())
        {
            // Load file in full
            uint32_t byteLoc = 0;
            raw_size = reader.tellg();
            reader.seekg(std::ios::beg);
            raw_file = new char[static_cast<size_t>(raw_size)];
            reader.read(raw_file, raw_size);
            reader.close();
        }
        else std::cout << "Error opening file!\n";
    }

    if (raw_file)
    {
        hot_patch_raw_image(raw_file, raw_size);

        // Write Raw
        {
            std::ofstream writer(dest, std::ios::binary | std::ios::trunc);

            if (writer.is_open())
            {
                writer.write(raw_file, raw_size);
                writer.close();
            }
            else std::cout << "Error writing file!\n";
        }
    }
    else return -1;

    return 0;
}

