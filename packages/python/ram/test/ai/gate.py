# Copyright (C) 2008 Maryland Robotics Club
# Copyright (C) 2008 Joseph Lisee <jlisee@umd.edu>
# All rights reserved.
#
# Author: Joseph Lisee <jlisee@umd.edu>
# File:  packages/python/ram/test/ai/gate.py

# Python Imports
import unittest

# Project Imports
import ram.ai.gate as gate

import ram.motion as motion
import ram.motion.basic

import ram.test.ai.support as support

class TestGate(support.AITestCase):
    def setUp(self):
        cfg = {
            'StateMachine' : {
                'States' : {
                    'ram.ai.gate.Dive' : {
                        'depth' : 7,
                        'speed' : 2,
                    },
                    'ram.ai.gate.Forward' : {
                        'speed' : 5,
                         'time' : 15
                    }
                }
            }
        }
        support.AITestCase.setUp(self, cfg = cfg)
    
    def testDive(self):
        self.machine.start(gate.Dive)
        
        # Ensure we actually started diving
        self.assertCurrentMotion(motion.basic.RateChangeDepth)
                
        # Now make sure we go to forward after diving
        self.injectEvent(motion.basic.Motion.FINISHED)   
        self.assertCurrentState(gate.Forward)   
                
        #self.assert_(self.motionManager.stopped)
        
    def testForward(self):
        # Make our timer blocks in the background
        self.timerBlock = True
        
        # Make sure we start driving forward
        self.machine.start(gate.Forward)
        self.assertEqual(5, self.controller.speed)
        
        # Now make sure we stop
        self.releaseTimer(self.machine.currentState().timer)
        self.assertEqual(0, self.controller.speed)
        
        # Make sure we hit the end state
        self.assert_(self.machine.complete)
    
    def testEndEvent(self):
        # Clear anything in the queue
        self.qeventHub.publishEvents()
        
        # Subscribe to end event
        self._complete = False
        def finished(event):
            self._complete = True
        self.qeventHub.subscribeToType(gate.COMPLETE, finished)
            
        # Make sure we get the final event
        self.timerBlock = True
        self.machine.start(gate.Forward)
        self.releaseTimer(self.machine.currentState().timer)
        self.qeventHub.publishEvents()
        self.assert_(self._complete)