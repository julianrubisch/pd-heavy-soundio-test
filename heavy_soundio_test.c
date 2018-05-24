#include "heavy_soundio_test.h"

static void write_callback(struct SoundIoOutStream *outstream,
        int frame_count_min, int frame_count_max)
{
    const struct SoundIoChannelLayout *layout = &outstream->layout;
    float float_sample_rate = outstream->sample_rate;
    struct SoundIoChannelArea *areas;
    int frames_left = frame_count_max;
    int err;

    
    int numOutputChannels = hv_getNumOutputChannels(context);

    // heavy stuff
    float **outBuffers = (float **) hv_malloc(numOutputChannels * sizeof(float *));
    for (int i = 0; i < numOutputChannels; ++i) {
      outBuffers[i] = (float *) hv_malloc(frame_count_max * sizeof(float));
    }

    hv_process(context, NULL, outBuffers, frame_count_max);

    while (frames_left > 0) {
        int frame_count = frames_left;    

        if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
            fprintf(stderr, "%s\n", soundio_strerror(err));
            exit(1);
        }

        if (!frame_count)
            break;

        for (int frame = 0; frame < frame_count; frame += 1) {
            for (int channel = 0; channel < layout->channel_count; channel += 1) {
                float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
                *ptr = outBuffers[channel][frame] * 0.5;
            }
        }

        if ((err = soundio_outstream_end_write(outstream))) {
            fprintf(stderr, "%s\n", soundio_strerror(err));
            exit(1);
        }

        frames_left -= frame_count;
    }
}

int main(int argc, const char *argv[]) {
    
  context = hv_teensy_fm_test_new(44100.0f);  
  int err;
  struct SoundIo *soundio = soundio_create();
  if (!soundio) {
      fprintf(stderr, "out of memory\n");
      return 1;
  }

  if ((err = soundio_connect(soundio))) {
      fprintf(stderr, "error connecting: %s\n", soundio_strerror(err));
      return 1;
  }

  soundio_flush_events(soundio);

  int default_out_device_index = soundio_default_output_device_index(soundio);
  if (default_out_device_index < 0) {
      fprintf(stderr, "no output device found\n");
      return 1;
  }

  struct SoundIoDevice *device = soundio_get_output_device(soundio, default_out_device_index);
  if (!device) {
      fprintf(stderr, "out of memory\n");
      return 1;
  }

  fprintf(stderr, "Output device: %s\n", device->name);

  struct SoundIoOutStream *outstream = soundio_outstream_create(device);
  if (!outstream) {
      fprintf(stderr, "out of memory\n");
      return 1;
  }
  outstream->format = SoundIoFormatFloat32NE;
  outstream->write_callback = write_callback;

  if ((err = soundio_outstream_open(outstream))) {
      fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
      return 1;
  }

  if (outstream->layout_error)
      fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(outstream->layout_error));

  if ((err = soundio_outstream_start(outstream))) {
      fprintf(stderr, "unable to start device: %s\n", soundio_strerror(err));
      return 1;
  }

  for (;;)
      soundio_wait_events(soundio);

  soundio_outstream_destroy(outstream);
  soundio_device_unref(device);
  soundio_destroy(soundio);
  hv_delete(context);
  return 0;
}