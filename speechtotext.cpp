#include "speechtotext.h"
#include <mainwindow.h>
#include <iostream>
#include <string>
#include <pocketsphinx.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>
#include <QThread>
#include <QString>
#include <QDebug>

using namespace std;

SpeechToText::SpeechToText()
{

}

ps_decoder_t *ps;                  // create pocketsphinx decoder structure
cmd_ln_t *config;                  // create configuration structure
ad_rec_t *ad;                      // create audio recording structure - for use with ALSA functions

int16 adbuf[4096];                 // buffer array to hold audio data
uint8 utt_started, in_speech;      // flags for tracking active speech - has speech started? - is speech currently happening?
int32 k;                           // holds the number of frames in the audio buffer
char const *hyp;                   // pointer to "hypothesis" (best guess at the decoded result)

void SpeechToText::run()
{
    config = cmd_ln_init(NULL, ps_args(), TRUE,
                "-hmm", "/home/menon/development/cmusphinx/models/model_v1/db.ci_cont",
                "-lm", "/home/menon/development/cmusphinx/models/model_v1/3802.lm",
                "-dict", "/home/menon/development/cmusphinx/models/model_v1/3802.dic",
                "-logfn", "/dev/null",
                NULL);

    ps = ps_init(config);
    ad = ad_open_dev("/dev/dsp", (int) cmd_ln_float32_r(config, "-samprate"));

    if(ad == NULL) {
        cout << "Failed to open audio device\n";
    }

    if (ad_start_rec(ad) < 0)
        cout << "Failed to start recording\n";

    if (ps_start_utt(ps) < 0)
        cout << "Failed to start utterance\n";


    while(true)
    {
        string decoded_speech = recognize_from_microphone();          // call the function to capture and decode speech
        cout << "You say: "<< decoded_speech << "\n" << endl;   // send decoded speech to screen

        if(MainWindow::flag == true)
        {
            // send signal

            //QThread::sleep(1);
            QString number = decodeNumber(QString::fromStdString(decoded_speech));

            qDebug() << "Number is: " << number << "\n";

            if(number == "") {
                number = "Nothing...";
            }
            emit progressChanged("You probably said: " + number + "\n");
            //emit progressChanged(QString::fromStdString("You say: " + decoded_speech));
            //number.clear();
            cout << "After emit" << endl;
        }
        decoded_speech.clear();
    }
    ad_close(ad);
}

string SpeechToText::recognize_from_microphone()
{
    ad_start_rec(ad);                                // start recording
    ps_start_utt(ps);                                // mark the start of the utterance
    utt_started = FALSE;                             // clear the utt_started flag

    cout << "Ready....\n";
    if(MainWindow::flag == true) {
        emit progressChanged("Ready...");
    }


    while(true)
    {
        k = ad_read(ad, adbuf, 4096);                // capture the number of frames in the audio buffer
        ps_process_raw(ps, adbuf, k, FALSE, FALSE);  // send the audio buffer to the pocketsphinx decoder

        in_speech = ps_get_in_speech(ps);            // test to see if speech is being detected

        if (in_speech && !utt_started) {             // if speech has started and utt_started flag is false
            utt_started = TRUE;                      // then set the flag
            cout << "Listening...\n";
            if(MainWindow::flag == true) {
                emit progressChanged("Listening...");
            }

        }
        if (!in_speech && utt_started) {             // if speech has ended and the utt_started flag is true
            ps_end_utt(ps);                          // then mark the end of the utterance
            ad_stop_rec(ad);                         // stop recording
            hyp = ps_get_hyp(ps, NULL );             // query pocketsphinx for "hypothesis" of decoded statement

            if(hyp == NULL) {
                return "you say nothing..";
            }
            return hyp;                              // the function returns the hypothesis
            break;                                   // exit the while loop and return to main
        }

    }
}

QString SpeechToText::decodeNumber(QString info)
{

    qDebug() << "info is: " << info << "\n";

    if(info == "you say nothing..") {
        return "nothing..";
    }

    QStringList list = info.split(" ");
    QString number = "";

    if(info.length() > 0)
    {
        for(int i = 0; i < list.size(); )
        {
            //qDebug() << "List element is : " << list[i] << "\n";

            if(list[i] == "ZIRO") {
                number = number + "0 ";
                i++;
            }
            else if(list[i] == "OAAN") {
                number = number + "1 ";
                i++;
            }
            else if(list[i] == "TOO") {
                number = number + "2 ";
                i++;
            }
            else if(list[i] == "TIRI") {
                number = number + "3 ";
                i++;
            }
            else if(list[i] == "FOUR") {
                number = number + "4 ";
                i++;
            }
            else if(list[i] == "PHAIB") {
                number = number + "5 ";
                i++;
            }
            else if(list[i] == "SIKS") {
                number = number + "6 ";
                i++;
            }
            else if(list[i] == "SEBHEN") {
                number = number + "7 ";
                i++;
            }
            else if(list[i] == "AEIT") {
                number = number + "8 ";
                i++;
            }
            else if(list[i] == "NAIN") {
                number = number + "9 ";
                i++;
            }
            else if(list[i] == "DOBOUL" && i + 1 < list.size())
            {
                if(list[i + 1] == "ZIRO") {
                    number = number + "0 ";
                    number = number + "0 ";
                    i += 2;
                }
                else if(list[i + 1] == "OAAN") {
                    number = number + "1 ";
                    number = number + "1 ";
                    i += 2;
                }
                else if(list[i + 1] == "TOO") {
                    number = number + "2 ";
                    number = number + "2 ";
                    i += 2;
                }
                else if(list[i + 1] == "TIRI") {
                    number = number + "3 ";
                    number = number + "3 ";
                    i += 2;
                }
                else if(list[i + 1] == "FOUR") {
                    number = number + "4 ";
                    number = number + "4 ";
                    i += 2;
                }
                else if(list[i + 1] == "PHAIB") {
                    number = number + "5 ";
                    number = number + "5 ";
                    i += 2;
                }
                else if(list[i + 1] == "SIKS") {
                    number = number + "6 ";
                    number = number + "6 ";
                    i += 2;
                }
                else if(list[i] == "SEBHEN") {
                    number = number + "7 ";
                    number = number + "7 ";
                    i += 2;
                }
                else if(list[i] == "AEIT") {
                    number = number + "8 ";
                    number = number + "8 ";
                    i += 2;
                }
                else if(list[i] == "NAIN") {
                    number = number + "9 ";
                    number = number + "9 ";
                    i += 2;
                }
                else
                    return "nothing";
            }
            else
                return "nothing";
            cout << "i : " << i << endl;
        }
        //qDebug() << "NUMBER: " << number << "\n";
     }
     cout << "Exit from decode .. " << endl;
     return number;
}
