<div align='center'>

<img src=https://github.com/SunriseMyG/Epitech-Teams/blob/main/screenshots/business.png alt="logo" width=500 height=500 />

<h1>Teams</h1>
<p>The goal of this project is to create a server and a CLI client. We had to design our own RFC protocol and data model in accordance with the technical specifications of the provided data library. We implemented the required commands and used the provided server and client libraries to print each event and data. Network communication is achieved through the use of TCP sockets.</p>

<h4> <span> · </span> <a href="https://github.com/StevenDeff/Epitech-Teams/blob/master/README.md"> Documentation </a> <span> · </span> <a href="https://github.com/StevenDeff/Epitech-Teams/issues"> Report Bug </a> <span> · </span> <a href="https://github.com/StevenDeff/Epitech-Teams/issues"> Request Feature </a> </h4>


</div>

# :notebook_with_decorative_cover: Table of Contents

- [About the Project](#star2-about-the-project)
- [Contributing](#wave-contributing)
- [License](#warning-license)
- [Contact](#handshake-contact)


## :star2: About the Project

### :camera: Screenshots
<div align="center"> <a href=""><img src="https://github.com/SunriseMyG/Epitech-Teams/blob/main/screenshots/image.png" alt='image' width='800'/></a> </div>
<div align="center"> <a href=""><img src="https://github.com/SunriseMyG/Epitech-Teams/blob/main/screenshots/image1.png" alt='image' width='800'/></a> </div>


## :toolbox: Getting Started

### :gear: Installation

GCC
```bash
sudo apt install build-essential
```


### :triangular_flag_on_post: Deployment

Compilation
```bash
make
```
```bash
export LD_LIBRARY_PATH=$(pwd)/libs/myteams:$LD_LIBRARY_PATH
```
Start
```bash
./myteams_server [port]
```
```bash
./myteams_cli [ip_of_machine] [port]
```


### :test_tube: Running Tests

Using client and command
* ### Features

  show help
    ```bash
      /help
    ```

  set the user_name used by client
    ```bash
      /login ["user_name"]
    ```

  disconnect the client from the server
    ```bash
      /logout
    ```

  get the list of all users that exist on the domain
    ```bash
      /users
    ```

  get information about a user
    ```bash
      /user ["user_uuid"]
    ```

  send a message to a user
    ```bash
    /send ["user_uuid"] ["message_body"]
    ```

  list all messages exchange with a user
    ```bash
    /messages ["user_uuid"]
    ```

  subscribe to the event of a team and its subdirectories (enable reception of all events from a team)
    ```bash
    /subscribe ["team_uuid"]
    ```

  list all subscribed teams or list all users subscribed to a team
    ```bash
    /subscribed ?["team_uuid"]
    ```

  unsubscribe from a team
    ```bash
    /unsubscribe ["team_uuid"]
    ```

  use specify a context team/channel/thread
    ```bash
    /use ?["team_uuid"] ?["channel_uuid"] ?["thread_uuid"] 
    ```

  based on what is being used create the sub resource
    ```bash
    /create
    ```

  based on what is being used list all the sub resources
    ```bash
    /list
    ```

  based on what is being used list the current
    ```bash
    /info
    ```

    * #### /Create
        When the context is not defined (/use):
        ```bash
          /create ["team_name"] ["team_description"] : create a new team
        ```
      
        When team_uuid is defined (/use "team_uuid"):
        ```bash
          /create ["channel_name"] ["channel_description"] : create a new channel
        ```
      
        When team_uuid and channel_uuid are defined (/use "team_uuid" "channel_uuid"):
        ```bash
          /create ["thread_title"] ["thread_message"] : create a new thread
        ```
      
        When team_uuid, channel_uuid and thread_uuid are defined (/use "team_uuid" "channel_uuid" "thread_uuid"):
        ```bash
          /create ["comment_body"] : create a new reply
        ```

    * #### /List

      When the context is not defined (/use):
      ```bash
      /list : list all existing teams
      ```
      
      When team_uuid is defined (/use “team_uuid”):
      ```bash
      /list : list all existing channels
      ```
      
      When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
      ```bash
      /list : list all existing threads
      ```
      
      When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
      ```bash
      /list : list all existing replies
      ```

    * #### /Info

      When the context is not defined (/use):
      ```bash
      /info : display currently logged user infos
      ```
      
      When team_uuid is defined (/use “team_uuid”):
      ```bash
      /info : display currently selected team infos
      ```
      
      When team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”):
      ```bash
      /info : display currently selected channel infos
      ```
      
      When team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”):
      ```bash
      /info : display currently selected thread infos
      ```



## :wave: Contributing

<a href="https://github.com/SunriseMyG"> <img src=https://github.com/SunriseMyG.png width=176 height=176 /> </a>
<a href="https://github.com/187Lucka"> <img src=https://github.com/187Lucka.png width=176 height=176 /> </a>

Contributions are always welcome!

see `contributing.md` for ways to get started

## :warning: License

MIT License

Copyright (c) 2024 StevenDeff/187Lucka

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## :handshake: Contact

Steven - [@twitter](https://x.com/AceTeeGG) - [@linkedin](linkedin.com/in/steven-deffontaine/) - steven.deffontaine@epitech.eu <br></br>
Lucka - [@linkedin](linkedin.com/in/lucka-valtriani-8a8551258/) - lucka.valtriani@epitech.eu

Project Link: [https://github.com/StevenDeff/Epitech-Teams](https://github.com/SunriseMyG/Epitech-Teams)
