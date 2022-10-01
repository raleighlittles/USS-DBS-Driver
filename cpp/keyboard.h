/**
 * @file  file-name
 * @author your name (you@domain.com)
 * @brief Based heavily on: https://www.kernel.org/doc/html/latest/input/uinput.html
 * @version 0.1
 * @date 2022-09-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <utility>
#include <map>
#include <linux/uinput.h>
#include <fcntl.h>
#include <stdexcept>
#include <string>
#include <string.h> // for memset()
#include <unistd.h>

class Keyboard
{
    public:

        Keyboard() {
            struct uinput_setup usetup;

            int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

            if (fd < 0) {
                throw std::runtime_error("Error opening uinput file descriptor. Double check that permissions are correct. Errno= " + errno);
            }

            mFileDescr = fd;

            usleep(1000);

            memset(&usetup, 0, sizeof(usetup));
            usetup.id.bustype = BUS_USB;

            // Uinput interface requires you to provide vendorID and productID,
            // so just choose some bogus values
            // but make sure they're not already in use: http://www.linux-usb.org/usb.ids
            usetup.id.vendor = 0xABBA;
            usetup.id.product = 0xBEEF;

            strcpy(usetup.name, "US Solid Precision Scale (USS-DBS28) Keyboard driver");

            if (ioctl(fd, UI_DEV_SETUP, &usetup) < 0) {
                throw std::runtime_error("Error with `UI_DEV_SETUP ioctl, errno=" + errno);
            }

            if (ioctl(fd, UI_DEV_CREATE) < 0) {
                throw std::runtime_error("Error with `UI_DEV_CREATE` ioctl, errno=" + errno);
            }

        }

        ~Keyboard() {
            ioctl(mFileDescr, UI_DEV_DESTROY);
            close(mFileDescr);
        }

    private:

        int mFileDescr;

        static const std::map<std::string, int> keyMap;

        void registerKeyboardEvents() {

            // Get the the uinput interface ready to register key events
            ioctl(mFileDescr, UI_SET_EVBIT, EV_KEY);

            // The list of keys that the device can produce
            for (const auto keyType : keyMap)
            {
                ioctl(mFileDescr, UI_SET_KEYBIT, keyType.second);
            }
        }
};

const std::map<std::string, int> Keyboard::keyMap ={ std::make_pair("0", KEY_0),
                                              std::make_pair("1", KEY_1),
                                              std::make_pair("2", KEY_2),
                                              std::make_pair("3", KEY_3),
                                              std::make_pair("4", KEY_4),
                                              std::make_pair("5", KEY_5),
                                              std::make_pair("6", KEY_6),
                                              std::make_pair("7", KEY_7),
                                              std::make_pair("8", KEY_8),
                                              std::make_pair("9", KEY_9),
                                              std::make_pair(".", KEY_DOT) };