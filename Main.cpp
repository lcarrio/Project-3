

#include <JuceHeader.h>
#include "TwitterPartyCalculator.h"
#include <string>
#include <iostream>
using namespace std;

// References used to create this class: https://docs.juce.com/master/classJUCEApplication.html
class twitterApp    : public juce::JUCEApplication
{
public:
       
        twitterApp()  {}
        ~twitterApp() {}
    // Sets the application so that no more than one instance is allowed.
    bool moreThanOneInstanceAllowed () override{
        return false;
    }
    // Calls quit when the OS tries to close the application.
    void systemRequestedQuit() override{
            quit();
    }
    const juce::String getApplicationName() override{
        return "Twitter Party Calculator";
    }
    const juce::String getApplicationVersion() override{
        return "1.0";
    }
    // When the app starts this function is called which creates a new instance of the MainWindow class in order to show the application window.
    void initialise (const juce::String& cl) override{
        mainPanel.reset (new AppWindow (getApplicationName(), new  MainContentComponent, *this));
    }
    void shutdown() override{
        mainPanel= nullptr;
    }
    
private:
    // Class for the application window, references used: https://docs.juce.com/master/tutorial_main_window.html
    
    class AppWindow    : public juce::DocumentWindow
    {
    public:
        JUCEApplication& app;
        AppWindow (const juce::String& name, juce::Component* c, JUCEApplication& a)
            : DocumentWindow (name, juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                                .findColour (ResizableWindow::backgroundColourId),
                              juce::DocumentWindow::allButtons),
              app (a)
        {
            setVisible (true);
            setUsingNativeTitleBar (true);
            setContentOwned (c, true);
            setResizable (true, false);
            centreWithSize (getWidth(), getHeight());
        }

        void closeButtonPressed() override
        {
            app.systemRequestedQuit();
        }
    };
    unique_ptr<AppWindow> mainPanel;
};
START_JUCE_APPLICATION (twitterApp)
