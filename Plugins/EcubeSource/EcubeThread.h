/*
   ------------------------------------------------------------------

   This file is part of the Open Ephys GUI
   Copyright (C) 2016 Open Ephys
   Copyright (C) 2014 Michael Borisov

   ------------------------------------------------------------------

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef __ECUBETHREAD_H_EC4CAD67__
#define __ECUBETHREAD_H_EC4CAD67__


#include <DataThreadHeaders.h>

#include <stdio.h>
#include <string.h>

class SourceNode;

#if JUCE_WINDOWS
    #ifdef ECUBE_SUPPORT
        #define ECUBE_COMPILE
    #endif
#endif

#ifdef ECUBE_COMPILE
    class EcubeDevInt;
#endif


class EcubeThread : public DataThread
{
public:
#ifdef ECUBE_COMPILE
    EcubeThread (SourceNode* sn);
    ~EcubeThread();

    void run() override;

    /** Fills the DataBuffer with incoming data. This is the most important
    method for each DataThread.*/
    bool updateBuffer() override;

    /** Returns true if the data source is connected, false otherwise.*/
    bool foundInputSource() override;

    /** Initializes data transfer.*/
    bool startAcquisition() override;

    /** Stops data transfer.*/
    bool stopAcquisition() override;

	int getNumChannels();

    /** Returns the number of continuous channels the data source can provide.*/
    int getNumDataOutputs(DataChannel::DataChannelTypes type, int subIdx) const override;

	int getNumTTLOutputs(int subIdx) const override;

    
    /** Returns the sample rate of the data source.*/
    float getSampleRate(int subIdx) const override;

    /** Returns the volts per bit of a given data channel.*/
    float getBitVolts(int chan) const;

    float getBitVolts(const DataChannel* chan) const override;

    void setDefaultNamingScheme(int scheme);

    bool usesCustomNames() const override;

    // Custom thread control functions
    void setSpeakerVolume(double volume);
    void setSpeakerChannel(unsigned short channel);

private:
    int numberingScheme;
    void setDefaultChannelNames() override;

    ScopedPointer<EcubeDevInt> pDevInt;

    double m_samplerate;
    bool acquisition_running;

#else
    /** Empty methods for non-Windows platforms **/
    bool updateBuffer()
    {
        return false;
    }
    bool foundInputSource()
    {
        return false;
    }
    bool startAcquisition()
    {
        return false;
    }
    bool stopAcquisition()
    {
        return false;
    }
    int getNumChannels()
    {
        return 0;
    }
    float getSampleRate()
    {
        return 0.0f;
    }
    float getBitVolts()
    {
        return 0.0f;
    }


#endif



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EcubeThread);
};

#endif  // __RHD2000THREAD_H_2C4CBD67__
