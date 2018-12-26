#include <Arduino.h>

double BPMtoMilli(int bpm) {
    return ((60.0 / bpm) * 1000.0);
}

String getBPMname(unsigned int bpm) {
    if (bpm < 40) {
        return "Grave";
    } else if (bpm >= 40 && bpm < 60) {
        return "Largo";
    } else if (bpm >= 60 && bpm < 66) {
        return "Larghetto";
    } else if (bpm >= 66 && bpm < 76) {
        return "Adagio";
    } else if (bpm >= 76 && bpm < 90) {
        return "Andante";
    } else if (bpm >= 90 && bpm < 105) {
        return "Moderato";
    } else if (bpm >= 105 && bpm < 115) {
        return "Allegretto";
    } else if (bpm >= 115 && bpm < 130) {
        return "Allegro";
    } else if (bpm >= 130 && bpm < 168) {
        return "Vivace";
    } else if (bpm >= 168 && bpm < 200) {
        return "Presto";
    } else {
        return "Prestissimo";
    }
}