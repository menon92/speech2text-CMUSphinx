#ifndef SPEECHTOTEXT_H
#define SPEECHTOTEXT_H

#include <QThread>
#include <QString>
#include <iostream>
#include <string>
using namespace std;

class SpeechToText : public QThread
{
    Q_OBJECT

    public:
        SpeechToText();

        void run();

        string recognize_from_microphone();

        QString decodeNumber(QString number);

    // Define signal:
    signals:
        void progressChanged(QString info);
};

#endif // SPEECHTOTEXT_H
