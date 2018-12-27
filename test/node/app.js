var colors = require("colors");
var SerialPort = require("serialport");
const fs = require("fs");
const COMPORT = "COM17";
var port = new SerialPort(COMPORT, {
  baudRate: 115200,
  autoOpen: false
});
const OUTPUT_DIR = "output/";
const LOG_FILE_EXT = ".txt";
var gfile;

main = (async function() {
  var file = await getNextFileName(OUTPUT_DIR, "file-", "", LOG_FILE_EXT);
  gfile = file;
  console.log(`${file}`.green);
  setInterval(async () => {
    try {
      console.log(getTime());
      await append(file, getTime() + `\r\n`);
    } catch (err) {
      throw err;
    }
  }, 1000);
  port.open(err => {
    if (err) {
      throw err;
    }
  });
})();

function getTime() {
  date = new Date(); //.toJSON();
  return date;
}

port.on("data", async function(data) {
  try {
    if (!gfile) {
      throw new Error(`ERROR >>>> ${gfile} undefined`);
    }
    result = await append(gfile, data.toString());
  } catch (err) {
    throw err;
  }
  console.log(`Appended:\r\n${result}`);
});

port.on("error", function(err) {
  console.log("Error: ", err.message);
});

port.on("open", function(err) {
  console.log("PORT", COMPORT, "Opened!");
  //   port.write("RST\r\n");
});

function getNextFileName(dir, prefix, suffix, ext) {
  return new Promise(async (resolve, reject) => {
    var exists;
    for (let i = 0; i < 50; i++) {
      filePath = dir + prefix + i + suffix + LOG_FILE_EXT;
      exists = await fileExists(filePath);
      if (exists) {
        resolve(filePath);
        return;
      }
    }
    reject("ERROR >>>>> Max 50 files are allowed!".red);
    return;
  });
}

function append(file, data) {
  return new Promise((resolve, reject) => {
    fs.appendFile(file, data, err => {
      if (err) {
        reject(err);
      } else {
        resolve(data);
      }
    });
  });
}

function fileExists(file) {
  return new Promise((resolve, reject) => {
    fs.access(file, fs.constants.F_OK, err => {
      if (err) {
        resolve(true);
      } else {
        resolve(false);
      }
    });
  });
}
