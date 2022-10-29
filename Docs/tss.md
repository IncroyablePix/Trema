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

If you want to explicitly set properties for the whole window, you may just use the global selector "#"

```css
  # {
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