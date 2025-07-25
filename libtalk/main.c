#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <stdlib.h>
#include <stdio.h>
static void list_audio_devices(const ALCchar *devices)
{
        const ALCchar *device = devices, *next = devices + 1;
        size_t len = 0;

        fprintf(stdout, "Devices list:\n");
        fprintf(stdout, "----------\n");
        while (device && *device != '\0' && next && *next != '\0') {
                fprintf(stdout, "%s\n", device);
                len = strlen(device);
                device += (len + 1);
                next += (len + 2);
        }
        fprintf(stdout, "----------\n");
}
void al_test(){
    ALCdevice *device;
    device = alcOpenDevice(NULL);
    if (!device)
        return;
    // Attach buffer 0 to source
    ALboolean enumeration;

    enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
    if (enumeration == AL_FALSE)
            return;
    list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
    ALCenum error;

    error = alGetError();
    if (error != AL_NO_ERROR)
            return;
    ALCcontext *context;
    context = alcCreateContext(device, NULL);
    if (!alcMakeContextCurrent(context))
        return;
    ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
    alListener3f(AL_POSITION, 0, 0, 1.0f);
    // check for errors
    alListener3f(AL_VELOCITY, 0, 0, 0);
    // check for errors
    alListenerfv(AL_ORIENTATION, listenerOri);
    ALuint source;
    alGenSources((ALuint)1, &source);
    // check for errors

    alSourcef(source, AL_PITCH, 1);
    // check for errors
    alSourcef(source, AL_GAIN, 1);
    // check for errors
    alSource3f(source, AL_POSITION, 0, 0, 0);
    // check for errors
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    // check for errors
    alSourcei(source, AL_LOOPING, AL_FALSE);
    // check for errros
    ALuint buffer;
    alGenBuffers((ALuint)1, &buffer);
    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop = AL_FALSE;

    alutLoadWAVFile("test.wav", &format, &data, &size, &freq, &loop);
    alBufferData(buffer, format, data, size, freq);
}
int main(){

}
