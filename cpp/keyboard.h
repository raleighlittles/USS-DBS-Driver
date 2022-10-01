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

            registerKeyboardEvents();

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


        /// @brief  Primary function of the class. Generates key events for a given string
        /// @param fileDescriptor 
        /// @param text 
        void generateKeyPressEvent(const std::string text)
        {
            for (const auto ch : text) {
                // First generate the "pressed" event
                emit(EV_KEY, mKeyMap.at(ch), 1);
                emit(EV_SYN, SYN_REPORT, 0);
                // Then the "released" event
                emit(EV_KEY, mKeyMap.at(ch), 0);
                emit(EV_SYN, SYN_REPORT, 0);
            }
        }

    private:

        int mFileDescr;

        static const std::map<char, int> mKeyMap;

        void registerKeyboardEvents() {

            // Get the the uinput interface ready to register key events
            if (ioctl(mFileDescr, UI_SET_EVBIT, EV_KEY) < 0) {
                throw std::runtime_error("Error setting Uinput to register keyboard type events");
            }

            // The list of keys that the device can produce
            for (const auto keyType : mKeyMap)
            {
                if (ioctl(mFileDescr, UI_SET_KEYBIT, keyType.second) < 0) {
                    throw std::runtime_error("Error encountered when registering keyboard events. Errno=" + errno);
                }
            }
        }

        void emit(int type, int code, int val)
        {
            struct input_event ie;

            ie.type = type;
            ie.code = code;
            ie.value = val;
            /* timestamp values below are ignored */
            ie.time.tv_sec = 0;
            ie.time.tv_usec = 0;

            if ( write(mFileDescr, &ie, sizeof(ie)) < 0 ) {
                throw std::runtime_error("Error writing to uinput file, errno=" + errno);
            }
        }
};

const std::map<char, int> Keyboard::mKeyMap ={ std::make_pair('0', KEY_0),
                                              std::make_pair('1', KEY_1),
                                              std::make_pair('2', KEY_2),
                                              std::make_pair('3', KEY_3),
                                              std::make_pair('4', KEY_4),
                                              std::make_pair('5', KEY_5),
                                              std::make_pair('6', KEY_6),
                                              std::make_pair('7', KEY_7),
                                              std::make_pair('8', KEY_8),
                                              std::make_pair('9', KEY_9),
                                              std::make_pair('.', KEY_DOT)
                                               };