# Activities
## Introduction
Like Android, a view exists as an Activity. An activity has multiple methods that it can use and override.

### Overridables
#### OnCreateView
First method called when an activity is pushed.
This method lets you create your actual view either:
- By calling LoadView, built-in method that takes a path to a .txml file.
- By creating your widgets with plain C++ code. This method is good if you don't want any resource files.

#### OnActivityStart
Called right after the view was created and made accessible.

### OnActivityEnd
Called when your activity quits.

#### OnActivityResult
You can call the StartActivityForResult method with a request code to load another Activity.
While this activity quits, it sends:
- The same request code which identifies the request.
- An intent containing the data you might want to transmit.
- A response code for simple communication.

When this "top" activity ends, the OnActivityResult method is called with this data provided.

#### OnActivityUpdate
Called on every frame. Useful for immediate mode updates.

### Other methods
#### LoadView
Loads a .txml file as view.

#### QuitApplication
Quits the application.

#### QuitActivity
Leaves the current activity and resumes last activity. Allows to provide return codes and intents.

#### 

## Activity Builders
A default ActivityBuilder exists for the default Activity constructor.
If you want to override this constructor for whatever reason, you will need to provide a specialized ActivityBuilder.

```c++
template<>
struct Trema::View::ActivityBuilder<SomeActivity>
{
    int DefaultRequestCode; 
    
    // You can pass your custom attributes to the ActivityBuilder constructor 
    ActivityBuilder<SomeActivity>(int defaultRequestCode) : 
            DefaultRequestCode(defaultRequestCode)
    {
        
    }
    
    // The CreateActivity then consumes the struct's attributes
    std::unique_ptr<SomeActivity> CreateActivity(Intent intent, std::shared_ptr<Window> window, uint16_t requestCode = -1)
    {
        auto activity = std::make_unique<SomeActivity>(std::move(intent), std::move(window), DefaultRequestCode);
        return std::move(activity);
    }
};
```

Some compilers will require you to put your specialization in the Trema::View namespace.