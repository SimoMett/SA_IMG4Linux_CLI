#include <iostream>
#include <cstring>
#include <map>

#include "IMGFile.h"

int main(int argc, char ** argv)
{
    using namespace std;

    int retCode=0;

    if(argc<=1)
    {
       cout<< "Usage:\n\tSA_IMG4Linux_CLI \"\\path\\to\\imgfile\\\" <options> ..\n\tSA_IMG4Linux_CLI -h"<<endl;
    }
    else
    {
        if(string(argv[1])=="-h")
        {
            cout<< "Usage:\n\tSA_IMG4Linux_CLI \"\\path\\to\\imgfile\\\" <options> .."<<endl;
            cout << "Available options:"<<endl;
            cout << "\t'-i' : infos of the IMG archive"<<endl;
            cout << "\t'-e' : extract <file>"<<endl;
        }
        else
        {
            //Options map initialization
            map<string, int> options;
            options.insert(pair<string, int>("-i", 'i'));
            options.insert(pair<string, int>("-e", 'e'));
            //TODO add other options

            if(argc<=2)
            {
                cout << "Invalid sintax. For help see '-h'" << endl;
            }
            else
            {
                int option = options[argv[2]];
                if (option)
                {
                    try
                    {
                        string archive = string(argv[1]);
                        IMGFile imgFile(archive);

                        switch (option)
                        {
                            case 'i'://Infos
                            {
                                cout << "Number of entries: " << imgFile.getNumberOfEntries() << endl;
                                break;
                            }
                            case 'e'://Extract
                            {
                                if (argc <= 3)
                                {
                                    cout << "Wrong sintax. Correct sintax: '-e <filename>'" << endl;
                                }
                                else
                                {
                                    unsigned int id;
                                    if (imgFile.getEntryByName(string(argv[3]), id))
                                    {
                                        cout << "ID: " << id << "\nExtracting.." << endl;
                                        imgFile.extractFile(id);
                                    }
                                    else
                                    {
                                        cout << "Entry not found" << endl;
                                    }
                                }
                                break;
                            }

                            default:
                            {

                            }
                        }
                    }
                    catch (std::runtime_error &e)
                    {
                        cerr << "runtime error" << endl;
                        cerr << e.what() << endl;
                        retCode = -1;
                    }

                }
                else
                {
                    cout << "Invalid option. For help see '-h'" << endl;
                }
            }
        }
    }
    return retCode;
}