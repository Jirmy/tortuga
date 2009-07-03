/*
 * Copyright (C) 2009 Robotics at Maryland
 * Copyright (C) 2009 Joseph Lisee <jlisee@umd.edu>
 * All rights reserved.
 *
 * Author: Joseph Lisee <jlisee@umd.edu>
 * File:  packages/control/test/include/MockTranslationalControllerBase.h
 */

#ifndef RAM_CONTROL_TEST_MOCKTRANSLATIONALCONTROLLERBASE_H_03_15_2009
#define RAM_CONTROL_TEST_MOCKTRANSLATIONALCONTROLLERBASE_H_03_15_2009

// Project Includes
#include "control/include/TranslationalControllerBase.h"

class MockTranslationalControllerBase :
    public ram::control::TranslationalControllerBase
{
public:
    MockTranslationalControllerBase(ram::core::ConfigNode config) :
        ram::control::TranslationalControllerBase(config) {}
    
    virtual ram::math::Vector3 translationalUpdate(
        double timestep,
        ram::math::Vector3 linearAcceleration,
        ram::math::Quaternion orientation,
        ram::math::Vector2 position,
        ram::math::Vector2 velocity)

    {
        ram::control::TranslationalControllerBase::translationalUpdate(
            timestep, linearAcceleration, orientation, position, velocity);
        return ram::math::Vector3::ZERO;
    }
};

#endif // RAM_CONTROL_TEST_MOCKTRANSLATIONALCONTROLLERBASE_H_03_15_2009
