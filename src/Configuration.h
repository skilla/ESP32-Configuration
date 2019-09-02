//
// Created by Sergio Zambrano on 01/09/2019.
//

#ifndef configuration_h_
    #define configuration_h_

    #include "Arduino.h"
    #include <EEPROM.h>

    class Configuration
    {
        public:
            Configuration(byte version, void * data_structure, unsigned long data_size);
            void clear();
            bool write();
            bool read();
            byte version();
            bool forceWrite();

        private:
            byte _version;
            unsigned long _data_size;
            byte * _data_structure;
            byte getVersion();
            void writeVersion(byte version);
    };

#endif //configuration_h_
