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

#### Icon
Sets the icon of the window. The last Icon element will be applied.
- src: The source file for the icon
- *content*: None

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