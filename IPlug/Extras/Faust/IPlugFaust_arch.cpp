<<includeIntrinsic>>

#define FAUSTFLOAT iplug::sample

#include "IPlugFaust.h"

/* BEGIN AUTO GENERATED BY THE FAUST COMPILER ... */
<<includeclass>>
/* ... END AUTO GENERATED BY THE FAUST COMPILER  */

using namespace iplug;

class Faust_mydsp : public IPlugFaust
{
public:
	Faust_mydsp(const char* name,
                const char* inputDSPFile = 0,
                int nVoices = 1,
                int rate = 1,
                const char* outputCPPFile = 0,
                const char* drawPath = 0,
                const char* libraryPath = FAUST_LIBRARY_PATH)
	: IPlugFaust(name, nVoices)
	{
	}

	void Init() override
	{
        ::dsp* tmp_dsp = new FAUSTCLASS();
        
        // Polyphony handling
        bool midi_sync = false;
        int nvoices = 0;
        MidiMeta::analyse(tmp_dsp, midi_sync, nvoices);
        
        if (nvoices > 0) {
            dsp_poly* dsp_poly = new FAUSTCLASS_POLY(tmp_dsp, nvoices, true);
            mMidiHandler.addMidiIn(dsp_poly);
            mDSP = std::unique_ptr<::dsp>(dsp_poly);
        } else {
            mDSP = std::unique_ptr<::dsp>(tmp_dsp);
        }
        
        // MIDI handling
        mDSP->buildUserInterface(mMidiUI.get());
        
		mDSP->buildUserInterface(this);
        
		BuildParameterMap();
		mInitialized = true;
	}
};

#undef FAUSTCLASS
