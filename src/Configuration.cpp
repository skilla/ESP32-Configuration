//
// Created by Sergio Zambrano on 01/09/2019.
//

#include "Configuration.h"

Configuration::Configuration(byte version, void * data_structure, unsigned long data_size)
{
    this->_version = version;

    this->_data_structure = static_cast<byte*>(data_structure);

    this->_data_size = data_size;
    if (data_size > EEPROM.length() - 1) {
        this->_data_size = EEPROM.length() - 1;
    }
}

void Configuration::clear()
{
    if (this->getVersion() == 0)
        return;

    this->writeVersion(0);

    for (long i = 0; i < this->_data_size; i++) {
        EEPROM.write(i + 1, 0);
    }
}

bool Configuration::write()
{
    if (this->getVersion() != this->version() && this->getVersion() != 0)
        return false;

    for (long i = 0; i < this->_data_size; i++) {
        EEPROM.write(i + 1, * (this->_data_structure + i));
    }

    return true;
}

bool Configuration::read()
{
    if (this->getVersion() != this->version())
        return false;

    for (long i = 0; i < this->_data_size; i++) {
        * (this->_data_structure + i) = EEPROM.read(i + 1);
    }

    return true;
}

bool Configuration::forceWrite()
{
    this->writeVersion(this->version());
    return this->write();
}

byte Configuration::version()
{
    return this->_version;
}

byte Configuration::getVersion()
{
    return EEPROM.read(0);
}

void Configuration::writeVersion(byte version)
{
    EEPROM.write(0, version);
}
