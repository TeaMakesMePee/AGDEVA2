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
