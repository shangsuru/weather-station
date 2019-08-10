const mongoose = require("mongoose");
const Schema = mongoose.Schema;

const SensorDataSchema = new Schema({
  temperature: Number,
  humidity: Number
})

const SensorData = mongoose.model("sensordata", SensorDataSchema);
module.exports = SensorData;