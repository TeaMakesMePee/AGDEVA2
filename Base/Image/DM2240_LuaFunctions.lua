-- SetToLuaFile
function SetToLuaFile(outputString, overwrite)
   --File
   local f;
   --Wipe the contents with new data.
   if overwrite == 1 then
      f = assert(io.open("Image//DM2240.lua", "w"))
   --Append with new data.
   elseif overwrite == 0 then
      f = assert(io.open("Image//DM2240.lua", "a"))
   end
   --Write to the file.
   f:write(outputString)
   --Close the file.
   f:close()
end

-- Calculate Distance Square
function CalculateDistanceSquare(x1,y1,z1,x2,y2,z2)
  --Calculate distance squared
  local distanceSquare = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1)
  --Print the result
  print(distanceSquare)
  -- Return the result
  return distanceSquare
end

-- Get the Min, Max, Average and number of values for a set of arguments
function GetMinMax(...)
  local minValue = -1
  local maxValue = -1
  local avgValue = -1
  local numValues = 0
  for i,v in ipairs(arg) do
    if minValue == -1 then
      minValue = v
    elseif v < minValue then
      minValue = v
    end

    if maxValue == -1 then
      maxValue = v
    elseif v > maxValue then
      maxValue = v
    end
    
    avgValue = avgValue + v
    numValues = numValues + 1
    end
  avgValue = avgValue / numValues
  return minValue, maxValue, avgValue, numValues
end