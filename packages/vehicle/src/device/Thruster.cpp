/*
 * Copyright (C) 2007 Robotics at Maryland
 * Copyright (C) 2007 Joseph Lisee <jlisee@umd.edu>
 * All rights reserved.
 *
 * Author: Joseph Lisee <jlisee@umd.edu>
 * File:  packages/vision/src/device/Thruster.cpp
 */

// STD Includes
#include <sstream>

// Project Includes
#include "vehicle/include/device/Thruster.h"
#include "vehicle/include/device/ThrusterCommunicator.h"
#include "vehicle/include/device/ThrusterCommand.h"

namespace ram {
namespace vehicle {
namespace device {

Thruster::Thruster(std::string name, std::string address,
                   double calibrationFactor) :
    Device(name),
    m_address(address),
    m_calibrationFactor(calibrationFactor)
{
    // Register thruster
    ThrusterCommunicator::registerThruster(this);

    // Preform a soft reset just to be safe
    ThrusterCommand* cmd = new ThrusterCommand(m_address, SOFT_RESET);
    ThrusterCommunicator::getSingleton().sendThrusterCommand(cmd);
}

void Thruster::setForce(double force)
{
    // Convert force here (using calibration factor)


    std::stringstream ss;
    ss << " " << (int)force;
    ThrusterCommand* cmd = new ThrusterCommand(m_address, SET_FORCE, ss.str());
    ThrusterCommunicator::getSingleton().sendThrusterCommand(cmd);
}
    
} // namespace device
} // namespace vehicle
} // namespace ram
