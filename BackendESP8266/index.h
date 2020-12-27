const char MainPage[] PROGMEM = R"=====(
<!DOCTYPE html>

<html>
    <head>
        <meta name = "viewport" content = "width=device-width, initial-scale=1">
        <meta charset="UTF-8">

        <link rel = "stylesheet" href = "https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css">
        <script src = "https://cdnjs.cloudflare.com/ajax/libs/jscolor/2.0.4/jscolor.min.js"></script>
        <script src = "https://cdn.jsdelivr.net/npm/@jaames/iro"></script>

        <title>Leduri Rares</title>
    </head>

    <body>
        <div class = "container-fluid">
            <div class = "row">
                <div class = "wheel" id = "ColorWheel"></div>
            </div>
    
            <div class = "row">
                <div class = "col-12">
                    <h6 id = "UserInfo"></h6>
                    <h6 id = "ModeInfo"></h6>
                </div>
            </div>
        </div>

        <div class = "container-fluid">
            <div class = "row">
                <div class = "col-12">
                    <h3 class = "AnimationTitle">Music Mode</h3>
                    <label class = "MusicSwitch">
                            <input type = "checkbox" autocomplete = "off" id = "MusicCheckbox">
                            <span class = "MusicSlider"></span>
                      </label>
                </div>
            </div>
        </div>

        <div class = "container-fluid">
            <div class = "row">
                <div class = "col-12">
                    <div class = "RangeSliderBox" id = "FadeBox">
                        <h3 class = "AnimationTitle">Fade</h3>
                        <input type = "range" min = "10" max = "250" class = "RangeSlider" id = "FadeSlider" autocomplete="off">
                        <h5 id = "FadeOutput"></h5>
                    </div>
                </div>
            </div>

            <div class = "row">
                <div class = "col-12">
                    <div class = "RangeSliderBox" id = "RomanticBox">
                        <h3 class = "AnimationTitle">Romantic</h3>
                        <input type = "range" min = "10" max = "250" class = "RangeSlider" id = "RomanticSlider" autocomplete="off">
                        <h5 id = "RomanticOutput"></h5>
                    </div>
                </div>
            </div>
        </div>    
    </body>
</html>

<style>
    body
    {
        background-color: #000000;
        overflow-x: hidden;
    }

    h1, h1, h3, h4, h5, h6
    {
        color: white;
    }

    .container-fluid
    {
        margin-top: 2.5%;
    }

    .row
    {
        text-align: center;
    }

    #ColorWheel
    {
        margin: 0 auto;
    }

    @media only screen and (max-width: 800px) 
    {
        .container-fluid
        {
            margin-top: 10%;
        }

        #ColorWheel
        {
            margin: 5% auto;
        }
    }

    #UserInfo
    {
        margin-top: 25px;
    }

    .RangeSliderBox
    {
        margin-left: calc(50% - 160px);
        margin-top: 20px;
        border-radius: 9px;
        text-align: center;
        width: 320px;
        height: 125px;
        margin-bottom: 50px;
    }

    #FadeBox
    {
        background-image: linear-gradient(to bottom right, rgb(0, 119, 255) , rgb(0, 255, 55));
    }

    #RomanticBox
    {
        background-image: linear-gradient(to bottom right, rgb(150, 0, 0) , rgb(252, 61, 61));
    }

    .AnimationTitle
    {
        padding-top: 5px;
    }

    .RangeSlider
    {
        -webkit-appearance: none;
        appearance: none;
        border-radius: 18px;
        outline: none;
        margin-left: 2.5%;
        width: 95%; 
        height: 30px; 
        background: #000000;
    }

    .RangeSlider::-webkit-slider-thumb 
    {
        -webkit-appearance: none; 
        appearance: none;
        width: 26px; 
        height: 26px; 
        background: #007EF4; 
        cursor: pointer;
        border-width: 0px;
        border-radius: 50%;
    }

    .RangeSlider::-moz-range-thumb 
    {
        width: 26px; 
        height: 26px; 
        background: #007EF4; 
        cursor: pointer; 
        border-width: 0px;
        border-radius: 50%;
    }

    #RomanticSlider::-webkit-slider-thumb
    {
        background: white; 
    }

    #RomanticSlider::-moz-range-thumb 
    {
        background: white;
    }

    .MusicSwitch
    {
        margin-top: 1%;
        position: relative;
        display: inline-block;
        width: 150px;
        height: 46px;
    }


    .MusicSwitch input 
    {
        opacity: 0;
        width: 0;
        height: 0;
    }

    .MusicSlider
    {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: rgb(97, 97, 97);
        -webkit-transition: .4s;
        transition: .4s;
        border-radius: 34px;
    }

    .MusicSlider:before 
    {
        position: absolute;
        content: "";
        height: 42px;
        width: 42px;
        left: 2px;
        bottom: 2px;
        background-image: url("https://www.freepnglogos.com/uploads/spotify-logo-png/spotify-icon-marilyn-scott-0.png");
        background-size: contain;
        -webkit-transition: .4s;
        transition: .4s;
        border-radius: 50%;
    }

    input:checked + .MusicSlider
    {
        background-image: linear-gradient(to top left, rgb(0, 119, 255) , rgb(0, 255, 55));
    }

    input:checked + .MusicSlider:before 
    {
        -webkit-transform: translateX(104px);
        -ms-transform: translateX(104px);
        transform: translateX(104px);
    }
</style>

<script>
    var User;
    var UserTime;
    var ThisUser = window.location.href.substring(window.location.href.indexOf("user=") + 5);
    var ThisTime;

    var Mode;
    var ModeDescription;
    var ModeDelay;
    var MusicMode;

    let Socket = new WebSocket("ws://IP:WS_PORT");

    Socket.onclose = function(event) 
    {
        if (event.wasClean) 
        {
            alert("Connection with the server was closed smoothly");
        } else 
        {
            alert("Connection with the server was closed unexpectedly");
        }
    };

    Socket.onerror = function(error) 
    {
        alert("Connection Error: " + String(error.message));
    };

    Socket.onmessage = function(event) 
    {
        ServerResponse = JSON.parse(event.data);

        if(ServerResponse["DataType"] == "Init")
        {
            /* Init User */
            User = ServerResponse["User"];
            UserTime = ServerResponse["UserTime"];
            document.getElementById("UserInfo").innerHTML = "Last changed by: " + (User[0].toUpperCase() + User.slice(1)) + " at " + UserTime;
            
            /* Init Color Changer with Current Color */
            RedValue = ServerResponse["RedValue"];
            GreenValue = ServerResponse["GreenValue"];
            BlueValue = ServerResponse["BlueValue"];

            var ColorWheel = new iro.ColorPicker("#ColorWheel",
            {
                color: "rgb(" + String(RedValue) + ", " + String(GreenValue) + ", " +  String(BlueValue) + ")",
                borderWidth: 2,
                borderColor: '#ffffff',
                width: 275
            });

            ColorWheel.on('color:change', function(color, changes)
            {
                var Color = ColorWheel.color.rgb;
                ThisTime = new Date().toLocaleTimeString('en-US', 
                { 
                    hour12: false, 
                    hour: "numeric", 
                    minute: "numeric",
                    second: "numeric"
                });

                let ColorsJSON = { 
                    Password: "PASSWORD",
                    Mode: "StaticColor",
                    User: ThisUser,
                    UserTime: ThisTime,
                    RedValue: Color.r, 
                    GreenValue: Color.g,
                    BlueValue: Color.b 
                };

                Socket.send(JSON.stringify(ColorsJSON));
            });
        
            /* Init Modes */
            Mode = ServerResponse["Mode"];
            ModeDescription = ServerResponse["ModeDescription"];
            document.getElementById("ModeInfo").innerHTML = "Current Mode: " + Mode + " " + ModeDescription;
            
            var MusicCheckbox = document.getElementById("MusicCheckbox");
            MusicMode = ServerResponse["MusicMode"];

            if(MusicMode == true)
            {
                MusicCheckbox.checked = true;
            }
            else 
            {
                MusicCheckbox.checked = false;
            }

            var FadeSlider = document.getElementById("FadeSlider");
            var FadeOutput = document.getElementById("FadeOutput");
            FadeOutput.innerHTML = "Delay: " + ServerResponse["ModeDelay"] + " ms";
            FadeOutput.value = String(ServerResponse["ModeDelay"])
            
            FadeSlider.oninput = function() 
            {
                FadeOutput.innerHTML = "Delay: " + this.value / 10 + " ms";

                ThisTime = new Date().toLocaleTimeString('en-US', 
                { 
                    hour12: false, 
                    hour: "numeric", 
                    minute: "numeric",
                    second: "numeric"
                });
                
                let FadeJSON = { 
                    Password: "PASSWORD",
                    Mode: "Fade",
                    User: ThisUser,
                    UserTime: ThisTime,
                    Delay: this.value / 10
                };

                Socket.send(JSON.stringify(FadeJSON));
            }
            
            var RomanticSlider = document.getElementById("RomanticSlider");
            var RomanticOutput = document.getElementById("RomanticOutput");
            RomanticOutput.innerHTML = "Delay: " + ServerResponse["ModeDelay"] + " ms";
            RomanticOutput.value = String(ServerResponse["ModeDelay"])
            
            RomanticSlider.oninput = function() 
            {
                RomanticOutput.innerHTML = "Delay: " + this.value / 10 + " ms";

                ThisTime = new Date().toLocaleTimeString('en-US', 
                { 
                    hour12: false, 
                    hour: "numeric", 
                    minute: "numeric",
                    second: "numeric"
                });
                
                let RomanticJSON = { 
                    Password: "PASSWORD",
                    Mode: "Romantic",
                    User: ThisUser,
                    UserTime: ThisTime,
                    Delay: this.value / 10
                };
            
                Socket.send(JSON.stringify(RomanticJSON));
            } 
        }
        if(ServerResponse["DataType"] == "UserInfo")
        {
            User = ServerResponse["User"];
            UserTime = ServerResponse["UserTime"];
            document.getElementById("UserInfo").innerHTML = "Last changed by: " + (User[0].toUpperCase() + User.slice(1)) + " at " + UserTime;
        }
        if(ServerResponse["DataType"] == "ModeInfo")
        {
            Mode = ServerResponse["Mode"];
            ModeDescription = ServerResponse["ModeDescription"];

            document.getElementById("ModeInfo").innerHTML = "Current Mode: " + Mode + " " + ModeDescription;
        }
    };

    document.getElementById("MusicCheckbox").onclick = function(){
        ThisTime = new Date().toLocaleTimeString('en-US', 
        { 
            hour12: false, 
            hour: "numeric", 
            minute: "numeric",
            second: "numeric"
        });

        let MusicJSON = { 
            Password: "PASSWORD",
            Mode: "MusicToggle",
            User: ThisUser,
            UserTime: ThisTime,
            State: this.checked
        };

        Socket.send(JSON.stringify(MusicJSON));
    };
</script>
)=====";
