var ThisUser = window.location.href.substring(window.location.href.indexOf("user=") + 5);
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
