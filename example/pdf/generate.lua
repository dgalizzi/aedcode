preamble = [[\documentclass[10pt,a4paper]{article}
\usepackage[latin1]{inputenc}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\begin{document}]]

print(preamble)

n = 1
handle = io.popen("ls ..")
for f in handle:lines() do
	if f:match(".*\.cpp") ~= nil then
		if f ~= "util.cpp" and f ~= "util_tree.cpp" then
			--print(f)
			ejemplon = "\\paragraph{Ejercicio " ..  n .. "}"
			n = n + 1
			print(ejemplon)

			file = io.open("../" .. f)
			pr = false;
			for lines in file:lines() do
				if pr then
					if lines:match(".*FIN.*") then
						break
					end
					line_underscore_hacked = lines:gsub("_", "\\_")
					print(line_underscore_hacked)
				elseif lines:match(".*COMIENZO.*") ~= nil then
					pr = true
				end
			end
			filename_underscore_hacked = f:gsub("_", "\\_")
			print("Resuelto en el archivo {\\tt " .. filename_underscore_hacked .. "}")
			print()
			file:close()
		end
	end
end

handle:close()

print("\\end{document}")
