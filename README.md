<p align="center">
  <h1 align="center">ESP8266 Smart Led Lights</h1>

  <p align="center">
    WiFi controlled Led Lights
    <br />
    <br />
    <a href="https://github.com/Dexter0-0/SmartLedLights-v2"><strong>Read the code »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Dexter0-0/SmartLedLights-v2/issues">Report Bug</a>
    ·
    <a href="https://github.com/Dexter0-0/SmartLedLights-v2/issues">Request Feature</a>
  </p>
</p>


<!-- TABLE OF CONTENTS -->
<details open="open">
  <br />
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#screenshots">Screenshots</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

There are a lot of Led Light Controllers out there but this one is highly customizable, responsive and can be controlled from anywhere in the world. You can also give acces to multiple people to control your Leds and see who changed what and when. At the moment, the Smart Led Lights come with this features:

<br />

Feature | Explanation
------------ | -------------
Static color | Choose one of 16.777216 colors
Music Mode | Turning the Music Mode ON will make the Leds sync with the music you are listening to on Spotify
Animate Current Color | Takes the current color and transitions between making it dimmer or brighter as fast or slow as you want
Fade | Transitions between randomly generated colors as fast or slow as you want
Romantic | Transitions between randomly generated shades of Red, Pink and Purple as fast or slow as you want
Monochrome | Transitions between black (turnt off) and bright white as fast or slow as you want

<br />
The Smart Led Lights have 3 components:
<br />
* Web and WebSocket Servers that run on an ESP8266 connected to the Leds
<br />
* The Users Device (Phone, Tablet, PC or Smart Fridge)
<br />
* A Python Script that gets the currently playing song and the data the Server needs to sync with the song
<br />

### Built With

Backend:
* [ESP8266WiFi](https://getbootstrap.com)
* [WiFiClient](https://getbootstrap.com)
* [ESP8266WebServer](https://getbootstrap.com)
* [WebSocketsServer](https://getbootstrap.com)
* [ArduinoJson](https://getbootstrap.com)
<br />
Frontend:
<br />
* [Bootstrap](https://getbootstrap.com)
* [iro.js](https://github.com/jaames/iro.js)
<br />
Python Script:
* [Websockets](https://getbootstrap.com)
* [Spotipy](https://getbootstrap.com)



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.
* npm
  ```sh
  npm install npm@latest -g
  ```

### Installation

1. Get a free API Key at [https://example.com](https://example.com)
2. Clone the repo
   ```sh
   git clone https://github.com/your_username_/Project-Name.git
   ```
3. Install NPM packages
   ```sh
   npm install
   ```
4. Enter your API in `config.js`
   ```JS
   const API_KEY = 'ENTER YOUR API';
   ```



<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_



<!-- SCREENSHOTS -->
## Screenshots
![plot](./Screenshots/WebPagePhoto.png)

<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Your Name - [@your_twitter](https://twitter.com/your_username) - email@example.com

Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Img Shields](https://shields.io)
* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Pages](https://pages.github.com)
* [Animate.css](https://daneden.github.io/animate.css)
* [Loaders.css](https://connoratherton.com/loaders)
* [Slick Carousel](https://kenwheeler.github.io/slick)
* [Smooth Scroll](https://github.com/cferdinandi/smooth-scroll)
* [Sticky Kit](http://leafo.net/sticky-kit)
* [JVectorMap](http://jvectormap.com)
* [Font Awesome](https://fontawesome.com)





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
[product-screenshot]: images/screenshot.png
