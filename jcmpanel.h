#ifndef JCMPANEL_H
#define JCMPANEL_H

enum jcmpanel_mpg_dir {
    JCMPANEL_MPG_DIR_NONE,
    JCMPANEL_MPG_DIR_CW,
    JCMPANEL_MPG_DIR_CCW,
};

struct jcmpanel_mpg_message {
    enum jcmpanel_mpg_dir dir;
    long long total_pulse;
};

#if 0
struct jcmpanel_knob_message {
    unsigned short value;
    unsigned char percent;
};
#endif

#define JCMPANEL_MAGIC              'e'
#define JCMPANEL_IOR_SIGNUM         _IOR(JCMPANEL_MAGIC, 0, int *)
#define JCMPANEL_IOR_EMG_IS_ACTIVE  _IOR(JCMPANEL_MAGIC, 1, int *)
#define JCMPANEL_IOR_MPG_DELTA_MS   _IOR(JCMPANEL_MAGIC, 2, int *)
#define JCMPANEL_IOW_MPG_DELTA_MS   _IOW(JCMPANEL_MAGIC, 3, int *)
#define JCMPANEL_IOR_MPG_MSG        _IOR(JCMPANEL_MAGIC, 4, struct jcmpanel_mpg_message *)
#define JCMPANEL_IOW_MPG_MSG        _IOW(JCMPANEL_MAGIC, 5, struct jcmpanel_mpg_message *)

#endif /* JCMPANEL_H */