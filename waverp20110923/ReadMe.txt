This version of WaveRP should be able to record 8-bit audio at
44.1 ksps and play 16-bit audio at 44.1 ksps.

The new WaveRP only produces contiguous wave files and requires
files that it plays to be contiguous.  Windows seems to always
make copied files contiguous.

Starting with a freshly formatted SD will insure all copied
files are contiguous from other Op Systems.

You must not access files while recording or playing wave
files.  WaveRP accesses files in raw mode from a thread
started by an interrupt routine.

the only html content is the WaveRP class.

I have included three sketches:

dapRP.pde - another hack to Ladyada's original

dapRPvol.pde - version of dap with software volume control.
               edit WaveRP.h and set DVOLUME nonzero to use this sketch.

PiSpeakRP.pde - A text-to-voice sketch that reads pi.  You need to
                put the files from the PiSpeakFiles folder on an SD.

WaveRecordPlay.pde  Demo of WaveRP functionality

to use the test sketches:

Download and install the latest SdFat from

http://code.google.com/p/sdfatlib/downloads/list
or
http://code.google.com/p/beta-lib/downloads/list

Put the WaveRP folder in your libraries folder

Compile and load the WaveRecordPlay.pde sketch.  

Open a serial window and type 'r' to record a file.
The sketch will print the ADC range, max value minus min value.
Type 's' to stop recording.
Type 'p' to play the file.

There are several #defines at the top of the sketch to set RECORD_RATE,
ADC_REFERENCE, MIC_ANALOG_PIN, MAX_FILE_SIZE, and other stuff.



Here is a bit more about WaveRecordPlay.pde

Command list for the sketch WaveRecordPlay.pde

a     play all WAV files in the root dir
c     clear - deletes all tracks
<n>d  delete track number <n>
h     help
l     list track numbers
p     play last track
<n>p  play track number <n>
r     record new track as last track
<n>r  record over deleted track <n>
v     record new track voice activated
<n>v  record over deleted track voice activated

Note: a maximum of 256 tracks are allowed on the SD card.

Type 'r' to record the first track to the file "TRACK000.WAV". 
The record level will be printed as a series of numbers.  The 
record level should hit peaks near but not at 255, the maximum level.
The record level for silence should be 2 or less.  This is the noise
level.

The file can be played by typing 'p'.  After a number of tracks have been
recorded, you can play a track by typing its number followed by a 'p'.
For example to play track five type '5p'.  

To delete track five type '5d'.  You can then record over track five 
by typing '5r'.  I have limited the '<n>r' to only record in "holes"
left by deleting tracks.  You may want to modify this by removing the
test "track > lastTrack".
