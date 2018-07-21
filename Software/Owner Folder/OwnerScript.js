// key value
let type1 = "problem"
let type2 = "level"
let type3 = "room"
let type4 = "sos_room"
let type5 = "sos_level"

//data
let problem = 0
let level = 0
let room = 0
let check_empty = 0
let sosRoom = 0
let sosLevel = 0

let getWeb = (type) => {
    $.ajax({
        type: "GET",
        url: `http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-${type}/view`,
        dataType: "text",
        success: function (response) {
           // console.log(response + type)
            if (type === 'problem') {
                if (response === '1') {
                    problem = 'tissue'
                } else if (response === '2') {
                    problem = clog
                } else if (response === '3') {
                    problem = 'light'
                }
            } else if (type === 'level') {
                if (response === '1') {
                    level = 1
                } else if (response === '2') {
                    level = 2
                }
            } else if (type === 'room') {
                if (response === '1') {
                    room = 1
                } else if (response === '2') {
                    room = 2
                } else if (response === '3') {
                    room = 3
                } else if (response === '4') {
                    room = 4
                }
            } else if (type === 'sos_room') {
                if(response === '0') {
                    sosRoom = 0
                }
                if (response === '1') {
                    sosRoom = 1
                    callSOS()
                } 
                if (response === '2') {
                    sosRoom = 2
                }
                if (response === '3') {
                    sosRoom = 3
                }
                if (response === '4') {
                    sosRoom = 4
                }
            } else if (type === 'sos_level') {
                if (response === '1') {
                    sosLevel = 1
                } else if (response === '2') {
                    sosLevel = 2
                }
            }

        },
        fail: function (response) {
            console.log(response)
        }
    });

}

let getAll = () => {
    getWeb(type1)
    getWeb(type2)
    getWeb(type3)
    getWeb(type4)
    getWeb(type5)


    sendTo()
}

let callSOS = () => {
    $('#SOS').html(`<div style="background-color: red">level: ${sosLevel} room: ${sosRoom}</div>`)
}

let sendTo = () => {
    if (problem === 'tissue') {
        $(`#1row${level}_${room}`).html(`<div class="alert alert-warning alert-dismissible fade show" role="alert">
        <h4>level: ${level} room: ${room}</h4>
        <button type="button" id="close-button1" class="close" data-dismiss="alert" aria-label="Close">
        <span aria-hidden="true">&times;</span>
        </button>
        </div>`)
    } else if (problem === 'clog') {
        $(`#2row${level}_${room}`).html(`<div class="alert alert-warning alert-dismissible fade show" role="alert">
        <h4>level: ${level} room: ${room}</h4>
        <button type="button" id="close-button2" class="close" data-dismiss="alert" aria-label="Close">
        <span aria-hidden="true">&times;</span>
        </button>
        </div>`)
    } else if (problem === 'light') {
        $(`#3row${level}_${room}`).html(`<div class="alert alert-warning alert-dismissible fade show" role="alert">
        <h4>level: ${level} room: ${room}</h4>
        <button type="button" id="close-button3" class="close" data-dismiss="alert" aria-label="Close">
        <span aria-hidden="true">&times;</span>
        </button>
        </div>`)
    }

}

let setup = () => {
    $('#sos-button').on('click', function () {
        $('#SOS').html(`<div>No Signal</div>`)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-sos_room/set?value=",
            data: {
                value: 0
            },
            dataType: "json",
            success: function (response) {
                
            }
        });
    })

    sosRoom = 0

    $('#')
}

let init = () => {
    setup()
    setInterval(getAll, 5000)
}

$(init)