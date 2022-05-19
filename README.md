
# Trema
ImGUI Object Oriented wrapper with XML view descriptors, styling and async event processing.

# Abstract
Have you ever had any consideration about GUI applications in C++? 
Trema is a wrapper around Dear ImGui that allows to write views as XML files and styling in a CSS. It uses GLFW & Vulkan as backend, Dear ImGui for components and TinyXML for XML files parsing.

**Since Dear ImGui stands for Immediate Mode GUI, the whole application will re-render for every frame. TL;DR => CPU & GPU Usage is greater than for Qt, wxWidgets, etc.**

# Features
Trema offers you to write full featured GUI applications with the view being only XML & Styling.
You can still use raw C++ components and add them manually to the GUI though.

A rough 10 lines of C++ code makes you able to open a rich GUI window fed by "TXML" and "TSS" files. 

Trema has its own styling language that goes by the name of TSS which has a CSS-like syntax with some extra stuff such as:
- Scoping/Nesting
- Variables
- ...

# TXML
The TXML which stands for Trema XML is used to create GUI applications. It roughly follows some kind of HTML structure. 
At root we have a **App** element which contains everything else.
As children, **App** allows only **Head** and **Body** elements which are very specifically defined.

## Head
Head is an element that will contain resource loading, global description and metadata about the application.
It allows the following elements as children:

### Descriptors
#### Font
Loads a fond into the program's memory.
- src: Source file for the Font (.ttf files)
- size: Size of the font
- name: The name that will be used later on to retrieve the font as a style
- *content*: None

#### Style
Loads a stylesheet and applies it *after all elements have been loaded*.
- src: The source file for the stylesheet
- *content*: Instead of a source file, you can inline the stylesheet code

#### Title
Sets the title of the window. The last Title element will be applied.
- *content*: The title string

#### WindowData
Sets the window main options. **Some options might recreate a context and a window which is costly.**
- fullscreen: Boolean value hinting the window to go fullscreen
- titlebar: Boolean value toggling the title bar. Enabled fullscreen overrides this value to true.
- width: The width of the window (Including the frame)
- height: The height of the window (Including the frame)
- *content*: None

### Body
Body is an element that will contain the actual elements. 
Right under the **body**, you need to have a *Layout* which will contain the different elements.
Be careful that **each element** on a same level should have a different *name*. A name acts as an identifier.

It allows the following elements as children:

### Layouts
Layouts allow *containers* as children. They fit element containers in the window.

#### MainDockSpace
A dock-space is a layout that allows you to move the different sub-windows around. 
It also allows you to take the sub-windows out of the main window.

Its subelements **must** have a *dockSlot* attribute that indicates the slot in which they are supposed to be located (left|center|right|top|bottom).


- name: The name of the element.
- saveLayout: The layout should be saved and the custom user settings for docking should override the programmed layout.
- *content*: Containers

#### StackSpace
A stack-space is a simple type of layout in which elements are just stacked one under the other.

- name: The name of the element.
- *content*: Containers

### Containers
A container is what the name is: it contains elements.

#### TopMenu
TopMenu is a special container that should appear only once in your layout. It consists in the top menu bar of the window.
TopMenu allows only one child, which is *SubMenu*.
- *content*: SubMenus

#### SubMenu
Can only be child of a *TopMenu*. Represents a "column" from the TopMenu.
It allows only *MenuOption* type elements.

- name: The name of the submenu that will be displayed.
- *content*: MenuOptions

#### WindowContainer
WindowContainer is a container that allows all simple gui elements. It defaults by stacking them from top to bottom.

- name: The name of the window that will be displayed on top.
- *content*: Elements

### Elements
Elements could also go by the name of widgets. They can only be a member of a container. 

#### MenuOption
MenuOption is an option for SubMenu. A menu option represents an option that can be clicked on.

- name: The name of the option that will be displayed.
- shortcut: The shortcut that will be displayed.

#### Radio
Radio is a "menu" consisting of mutually exclusive options.
It allows only *Option* elements.

- name: The name of the Radio and default label also.
- *content*: The different Option elements.

#### Combo
A Combo, AKA a "Select" is a list component from which you can select one unique option.
It only allows *Option* elements.

- name: The name of the select and default label also.
- *content*: The different Option elements.

#### Option
An option is an abstract component that relies on its parent (Radio/Combo) for display.

- name: The name of the option (Has precedence over content).
- *content*: The name of the option.

#### Button
A button doesn't need much explanation.

- name: The name of the button and the text displayed on it (Has precedence over content).
- *content*: The name of the button and the text displayed on it.

#### Text
Text is just readonly plain text.

- name: The text to be displayed (Has precedence over content).
- *content*: The text to be displayed.

#### Checkbox
A checkbox is a binary component which has two states : checked and unchecked.

- name: The name of the checkbox and the text displayed beside it (Has precedence over content).
- *content*: The name of the checkbox and the text displayed beside it.

#### Table
A table is a flexible two-dimensional grid containing a header and tuples (rows).

- name: The name of the table (Not useful).
- headers: Different headers for the table with ';' as a separator between them.
- *content*: The different *TableRow* elements.

#### TableRow
A table row is a flexible tuple or row for the *Table* element, and cannot be used outside of it.

- *content*: The different elements **must** comply to two conditions:
  - Being atomic elements.
  - Summing up to the same amount as the number of headers of the table.

#### TextInput
A text input is a field that allows the user to write single line text. 

- name: The name of the input and the default label (Has precedence over content).
- *content*: The name of the input and the default label.

#### TextArea
A text area is a field that allows the user to write multi-line text.

- name: The name of the text area and the default label (Has precedence over content).
- *content* The name of the text area and the default label.

#### Separator
A straight line.

#### SliderFloat
A float number selector in shape of a ranged slider.

- name: The name of the slider and the default label (Has precedence over content).
- min: The lower limit of the range
- max: The upper limit of the range
- *content*: The name of the slider and the default label.

#### SliderInt
An int number selector in shape of a ranged slider.

- name: The name of the slider and the default label (Has precedence over content).
- min: The lower limit of the range
- max: The upper limit of the range
- *content*: The name of the slider and the default label.

#### ColorPicker
A square shaped color picker from which you can get a color in several formats.

- name: The name of the color picker and the default label (Has precedence over content).
- preview: Small preview window for the selected color.
- input: Input text for hex formatted colors.
- *content*: The name of the color picker and the default label.

#### Image
An image that you can load and display.
- name: The name of the image.
- src: The source file for the image
- *content*: NOP

# TSS
TSS (Trema Style Sheet) is a styling language specific to Trema which is used to style components without having to do it in C++.
Its syntax strongly resembles to CSS with features such as scoping for shared variables.

## Declaring a variable
You can declare a global property for the stylesheet. This variable will be applied for the whole window.

### Syntax
```css
  red: 0xCC0000FF;
```

We can note several things:
- Colours are always in RGBA format
- The assigning operator is a colon
- Lines end with a semicolon

Also, variable names must begin with a letter and can contain numbers, letters, hyphens or underscores.

### Variable types
There are three variable types :
- **bool**: true or false
- **number**: 64bits signed integers or floats
- **string**: whatever text delimited by a couple of single or double quotes

```css
  myText: "Some random text";
  myOtherText: 'Some text with single quotes';

  myFloatNumber: -.5;
  myIntegerNumber: 256;
  mySecondFloat: 0.50;

  myBool: true;
```

### Copying
You can also copy a variable that has already been assigned a value.

```css
  invisible: 0x0;
  text-color: invisible;
```

## Scopes
Variables defined outside a scope will be affected to the window in its entirety.
To apply a variable to a specific component, you will need to define them inside a scope.

```css
  #element {
    text-color: 0xCC0000FF;
  }
```

This code will apply a reddish text colour for the element with the "element" id. 
You can also nest scopes to copy their variables.

```css
  scope {
    red: 0xCC0000FF;

    #element {
      text-color: red;
    }
  }
```

## Properties
Your own variables are not very useful if you don't bind them with the actual UI.
Some properties apply themselves to the UI. 

### text-color
The color of the text...

Admits only integer numbers in RGBA form.

### text-color-disabled
The color of the text when disabled (buttons, etc.).

Admits only integer numbers in RGBA form.

### widget-background-color
The background color of widgets such as text inputs etc.

Admits only integer numbers in RGBA form.

### widget-background-color-hover
The background color of widgets such as text inputs etc. when hovered with mouse.

Admits only integer numbers in RGBA form.

### widget-background-color-active
The background color of widgets such as text inputs etc. when they have focus.

Admits only integer numbers in RGBA form.

### button-color
The background color for buttons.

Admits only integer numbers in RGBA form.

### button-color-hover
The background color for buttons when hovered with mouse.

Admits only integer numbers in RGBA form.

### button-color-active
The background color for buttons when they are clicked onto.

Admits only integer numbers in RGBA form.

### menu-background-color
The background color of the menu bar.

Admits only integer numbers in RGBA form.

### background-color
The background color for a window container. 

Admits only integer numbers in RGBA form.

### header-color
The color for a window container header.

Admits only integer numbers in RGBA form.

### header-color-active
The color for a window container header when selected.

Admits only integer numbers in RGBA form. 

### table-header-color
The color for the header row of a table.

Admits only integer numbers in RGBA form.

### popup-background-color
The background color for a popup window.

Admits only integer numbers in RGBA form.

### slidergrab-color
The color of a slider grab.

Admits only integer numbers in RGBA form.

### slidergrab-color-active
The color of a slider grab when focused.

Admits only integer numbers in RGBA form.

### opacity
The opacity for an element.

Admits floating point numbers in a 0 to 1 range.

### orientation
The orientation for elements inside a container.

Admits strings such as "vertical" and "horizontal".

### window-padding-x
The horizontal padding from a window's border.

Admits unsigned integer and floating point numbers.

### window-padding-y
The vertical padding from a window's border.

Admits unsigned integer and floating point numbers.

### window-rounding
Rounding for free-roaming windows' corners.

Admits unsigned integer and floating point numbers.

### frame-padding-x
The horizontal padding from a widget's border (input text, etc.).

Admits unsigned integer and floating point numbers.

### frame-padding-y
The vertical padding from a widget's border (input text, etc.).

Admits unsigned integer and floating point numbers.

### frame-rounding
Rounding for widgets' corner.

Admits unsigned integer and floating point numbers.

### font
Font for texts.

Admits unsigned integer and floating point numbers.

### header
Window containers should have a header.

Admits boolean values.

### width
The width of the element.

Admits strings in two formats:
- "10px" - absolute
- "10%" - relative to the container

### height
The height of the element.

Admits strings in two formats:
- "10px" - absolute
- "10%" - relative to the container

### margin-top
The margin on the top of the element.

Admits strings in two formats:
- "10px" - absolute
- "10%" - relative to the container

### margin-right
The margin on the right of the element.

Admits strings in two formats:
- "10px" - absolute
- "10%" - relative to the container

### margin-bottom
The margin on the bottom of the element.

Admits strings in two formats:
- "10px" - absolute
- "10%" - relative to the container

### margin-left
The margin on the left of the element.

Admits strings in two formats:
- "10px" - absolute
- "10%" - relative to the container

# Installation/Build

## Dependencies
This project has one dependency that you will need to install:
- Vulkan

Other dependencies are embedded:
- GLFW
- Dear ImGUI
- TinyXML

Those are just included in the project, and it's *better for you* since it doesn't require any action from your side.
Since they are statically linked, which has its downsides too, you might want to dynamically link them, but the goal of this project is to keep things as simple as possible.

### Vulkan
You just have to install [Vulkan SDK](https://vulkan.lunarg.com/) and CMake will handle everything else.
If not done, you should set the **VK_SDK_PATH** environment variable as well to point to your Vulkan installation.

## Actual build
As a cmake project it's pretty easy to build the project.
Once everything previously mentioned done, make sure you have **CMake 3.20** installed.
Open a terminal and navigate to the root directory of the project.

### Linux

You might need to install some extra windowing packages:

#### CMake
If you struggle installing CMake 3.20+, do not install it with apt or such. Try with **pip**
```shell
sudo pip install cmake
```

### External GUI dependencies 
You might need to install the following libraries
```shell
sudo apt-get install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev
```

and Vulkan itself

```shell
sudo apt install vulkan-sdk
```

```shell
cmake -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build --target all
```

### Windows
#### MSVC
```shell
cmake -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A x64 -S . -B build
cmake --build build --target ALL_BUILD --config Release
```

N.-B.: The binaries will be built to *.\build\bin\Release*, but the resource files will be sent to *.\build\bin* and I didn't find how to fix this yet, so you have to manually change the files' location.

#### MinGW
```shell
cmake -G "MinGW Makefiles" -S . -B build
cmake --build build
```

This will build all the binaries including:
- Trema_Test: The test suite
- Trema_Sample: A sample program that shows some capabilities
- Trema: The shared library that contains all the functionalities

to the *build/bin/* directory.

Also, files such as fonts and resources will be copied to the same directory to be read by the sample executable.

## Test project
Though not exhaustive, there is a test project that has a dependency on [Catch2](https://github.com/catchorg/Catch2), which is also embedded in this project.

## Toolchains
This project has been tested with the following toolchains :

### Windows
- MinGW64     11.1.0
- MSVC x64    19.16.27043.0

I would personally recommend to use MSVC on Windows since it doesn't require to provide any extra .dll with deployed version but MinGW is fine too.

### Linux
- g++   

### MacOS
- none
