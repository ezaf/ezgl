# Main Object Interface

Describes the minimum-required interface for `root["main"]`.

## Minimum Requirements

Regardless of which graphics API binding you are using, `root["main"]` must
contain at least the following,

```json
"main": {
    "plugins": [
        "EzGL_*"
    ],
    "components": [
        "MainEvent",
        "MainLogic",
        "MainRender"
    ]
}
```

where `EzGL_*` is the name of the graphics API binding in use (such as
`EzGL_SDL`). An `EzGL_*`shared object file must be located in the same
directory as the main executable.

## Data Fields

Including any of these in your main json file is not strictly necessary as your
graphics API binding should have these set to sensible or automatically
detected defaults. For some of them it would be nonsensical to include them as
they are only meant to be accessed at runtime such as `"dt"` and `"t"`.

Data Field         | Description
:----------------- | :----------
`"bordered"`       | Whether the window has a border.
`"dt"`             | Time (s) since last frame.
`"display_height"` | Height of the window itself.
`"display_width"`  | Width of the window itself.
`"dt_max"`         | Graphics and physics time step cieling (s).
`"fullscreen"`     | Whether the window is in desktop fullscreen mode.
`"icon"`           | Application icon png file.
`"pause"`          | If set to `true`, pauses all object updates **including rendering**.
`"refresh_rate"`   | Graphics and physics refresh rate.
`"render_height"`  | Rendered/Logical resolution height within window.
`"render_width"`   | Rendered/Logical resolution width within window.
`"scaling"`        | `"nearest"` or `"linear"`. You're more likely to use the latter.
`"self_destruct"`  | Program will self destruct after this many seconds. Useful for automated build tests.
`"show_cursor"`    | Whether the mouse cursor is shown.
`"quit"`           | If set to `true`, the program will exit after the current frame.
`"t"`              | Unix time (ms).
`"title"`          | Application name.
`"vsync"`          | Whether vertical-sync is enabled.

All frame rate and timing code is handled internally by EzGL. Therefore it is
not the responsibility of any component to assign `"dt"`, `"dt_max"`,
`self_destruct`, or `"t"`.

If you want to enter fullscreen borderless mode, have both `"bordered"` and
`"fullscreen"` set to `false` and have both `"display_height"` and
`"display_width"` set to either their default values or `null`.

## Controls

The format of `root["main"]["controls"]` follows that of any other control
subgroup. Consult the `Control` documentation for more information.

Controls for the main object are optional. Toggles are only supported for
`"bordered"`, `"fullscreen"`, `"pause"`, `"show_cursor"`, and `"quit"`.

## Spawning in Objects

To add objects to the universe during initialization, specify the type and
quantity inside `root["main"]["objects"]`,

```json
"main": {
    "objects": {
        "MyObjectA": 3,
        "MyObjectB": 1
    }
}
```

where `MyObjectA` et al. must have their own respective data blocks in the
root, for example, `root["MyObjectA"]`.

Components can spawn objects in at runtime using `Object::Create`, where the
provided object name has the same requirements as the `MyObjectA` example
above.

## Example

Below is a fully featured example that includes all of the above mentioned
material. Definitions for `"apple"` and `"banana"` are left blank.

```json
{
    "main": {
        "title": "EzGL Demo",
        "icon": null,
        "render_width": 1920,
        "render_height": 1080,
        "display_width": 1280,
        "display_height": 720,
        "fullscreen": false,
        "bordered": true,
        "scaling": "linear",
        "refresh_rate": null,
        "vsync": true,
        "dt_max": 0.1,
        "show_cursor": true,
        "controls": {
            "quit": "ESCAPE",
            "pause": "BACKQUOTE",
            "show_cursor": "F9",
            "bordered": "F10",
            "fullscreen": "F11"
        },
        "plugins": [
            "EzGL_SDL"
        ],
        "components": [
            "MainEvent",
            "Control",
            "MainLogic",
            "MainRender"
        ],
        "objects": {
            "apple": 7,
            "banana": 3
        }
    },

    "apple": { },

    "banana": { }
}
```
