#pragma once
#include <string>
#include <functional>

namespace ikt::Menu {
class Option;

class Submenu {
public:
    Submenu(std::string title, std::string subTitle)
        : mTitle(title)
        , mSubtitle(subTitle) {

    }
    void AddEntry(std::unique_ptr<Option> entry) {
        mOptions.push_back(std::move(entry));
    }

protected:
    std::string mTitle;
    std::string mSubtitle;
    std::vector<std::unique_ptr<ikt::Menu::Option>> mOptions;
    uint32_t mCurrentOptionIndex;
};



class Option{
public:
    Option(std::string text, std::string details) 
    : mSelected(false)
    , mText(text)
    , mDetails(details)
    , mCbSelectAction([]{})
    , mCbLeftAction([]{})
    , mCbRightAction([]{}) {
        
    }
    Option(std::string text, std::string details, std::function<void()> cbSelect, 
        std::function<void()> cbLeft, std::function<void()> cbRight)
    : mSelected(false)
    , mText(text)
    , mDetails(details)
    , mCbSelectAction(std::move(cbSelect))
    , mCbLeftAction(std::move(cbLeft))
    , mCbRightAction(std::move(cbRight)) {

    }

protected:
    bool mSelected;
    std::string mText;
    std::string mDetails;
    std::function<void()> mCbSelectAction;
    std::function<void()> mCbLeftAction;
    std::function<void()> mCbRightAction;
};

// Just toggles on select action
class ToggleOption : public Option {
public:
    ToggleOption(std::string text, std::string details, bool* toggle)
    : Option(text, details)
    , mToggle(toggle) { }

protected:
    bool* mToggle;
};

// Only changes value pointed to.
template <typename T>
class ValueOption : public Option {
public:
    ValueOption(std::string text, std::string details, T* value)
        : Option(text, details)
        , mValue(value)
    {
        
    }
    ValueOption(std::string text, std::string details, T* value, std::function<void()> cbSelect)
        : Option(text, details, cbSelect, [] {}, [] {})
        , mValue(value) { }

protected:
    T* mValue;
};

// Only scrolls left/right through pointed-to list/vector.
template <typename T>
class ListOption : public Option {
public:
    ListOption(std::string text, std::string details, std::vector<T>* list, std::function<void()> cbIndexChanged)
    : Option(text, details)
    , mList(list)
    , mCbIndexChanged(cbIndexChanged) {
    }

    ListOption(std::string text, std::string details, std::vector<T>* list, std::function<void()> cbIndexChanged, std::function<void()> cbSelect)
    : Option(text, details, cbSelect, []{}, []{})
    , mList(list)
    , mCbIndexChanged(cbIndexChanged) {

    }

protected:
    std::vector<T>* mList;
    std::function<void()> mCbIndexChanged;
};

// panelText[0] = title
// see OptionPlus
class AdvancedOption : public Option {
public:
    AdvancedOption(std::string text, std::string details, std::vector<std::string> panelText)
        : Option(text, details)
    , mPanelText(panelText){ }

    AdvancedOption(std::string text, std::string details, std::vector<std::string> panelText,
                   std::function<void()> cbSelect, std::function<void()> cbLeft, std::function<void()> cbRight)
        : Option(text, details, cbSelect, cbLeft, cbRight) { }

protected:
    std::vector<std::string> mPanelText;
};

class MenuOption : public Option {
public:
    MenuOption(std::string text, std::string details, Submenu* menuGoto)
        : Option(text, details)
        , mNextMenu(menuGoto){ }

protected:
    Submenu* mNextMenu;
};

class Menu {
public:
    Menu(Submenu* head);
    void Render() {}
protected:
    Submenu* mCurrentMenu;
};

class IMenu {
public:
    IMenu() {
    }
protected:
    virtual ~IMenu() = default;
};
}
