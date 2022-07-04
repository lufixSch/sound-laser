#include <alsa/asoundlib.h>
#include <bcm2835.h>
#include <chrono>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

#include "speaker.hpp"

char data[3] = { 0x12, 0xAB, 0x34 };
char buf[3];

int main(int, char**) {
  std::cout << "Hello, world!\n";

  if (!bcm2835_init()) {
    std::cerr << "bcm2835_init failed. Are you running as root??\n";
    return 1;
  }

  // Speaker* speaker = Speaker::instance();
  // speaker->run_thread();

  int i;
  int err;
  char* buffer;
  int buffer_frames = 128;
  unsigned int rate = 44100;
  snd_pcm_t* capture_handle;
  snd_pcm_hw_params_t* hw_params;
  snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

  if ((err = snd_pcm_open(&capture_handle, "bluealsa", SND_PCM_STREAM_CAPTURE, 0)) < 0) {
    fprintf(stderr, "cannot open audio device (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "audio interface opened\n");

  if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
    fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "hw_params allocated\n");

  if ((err = snd_pcm_hw_params_any(capture_handle, hw_params)) < 0) {
    fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "hw_params initialized\n");

  if ((err = snd_pcm_hw_params_set_access(capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
    fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "hw_params access setted\n");

  if ((err = snd_pcm_hw_params_set_format(capture_handle, hw_params, format)) < 0) {
    fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "hw_params format setted\n");

  if ((err = snd_pcm_hw_params_set_rate_near(capture_handle, hw_params, &rate, 0)) < 0) {
    fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "hw_params rate setted\n");

  if ((err = snd_pcm_hw_params_set_channels(capture_handle, hw_params, 1)) < 0) {
    fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "hw_params channels setted\n");

  if ((err = snd_pcm_hw_params(capture_handle, hw_params)) < 0) {
    fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "hw_params setted\n");

  snd_pcm_hw_params_free(hw_params);

  fprintf(stdout, "hw_params freed\n");

  if ((err = snd_pcm_prepare(capture_handle)) < 0) {
    fprintf(stderr, "cannot prepare audio interface for use (%s)\n", snd_strerror(err));
    exit(1);
  }

  fprintf(stdout, "audio interface prepared\n");

  size_t len = 128 * snd_pcm_format_width(format) / 8;
  buffer = (uint16_t*)malloc(len);

  fprintf(stdout, "buffer allocated\n");

  for (i = 0; i < 10; ++i) {
    if ((err = snd_pcm_readi(capture_handle, buffer, buffer_frames)) != buffer_frames) {
      fprintf(stderr, "read from audio interface failed (%s)\n", err, snd_strerror(err));
      exit(1);
    }

    fprintf(stdout, "read %d done\n", i);
  }

  for (i = 0; i < len; i += 2) {
    //    std::cout << int(buffer[i]) << " \t" << int(buffer[i + 1]) << "\n";
    uint16_t val = ((uint16_t)buffer[i] << 8) + buffer[i + 1];

    std::cout << val << "\n";
  }

  free(buffer);

  fprintf(stdout, "buffer freed\n");

  snd_pcm_close(capture_handle);
  fprintf(stdout, "audio interface closed\n");

  bcm2835_close();

  return 0;
}
