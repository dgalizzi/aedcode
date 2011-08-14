preamble = [[\documentclass[10pt,a4paper]{article}
\usepackage[latin1]{inputenc}
\usepackage{amsmath}
\usepackage{amsfonts}
\usepackage{amssymb}
\begin{document}]]

print(preamble)

body = {}

handle = io.popen("ls ..")
for f in handle:lines() do
	if f:match(".*\.cpp") ~= nil then
		if f ~= "util.cpp" and f ~= "util_tree.cpp" then

			file = io.open("../" .. f)
			pr = false;
			descr = ""
			keys = {}
			for lines in file:lines() do
				if pr then
					if lines:match(".*FIN.*") then
						break
					end


					keywords = lines:match(".*keywords: (.*)")
					if keywords then
						for w in keywords:gmatch("(.-), ") do
							keys[#keys+1] = w
						end
						keys[#keys+1] = lines:match(".*, (.*)") or lines:match(".*: (.*)")
						break
					end

					line_underscore_hacked = lines:gsub("([^\\])_", "%1\\_")
					if not lines:match(".*$.*") then
						descr = descr .. line_underscore_hacked
					else
						descr = descr .. lines
					end
				elseif lines:match(".*COMIENZO.*") ~= nil then
					pr = true
				end
			end
			if not descr:match(".*WIKI.*") then
				filename_underscore_hacked = f:gsub("_", "\\_")
				for i=1, #keys do
					if body[keys[i]] == nil then
						body[keys[i]] = {}
					end
					-- MADNESS
					body[keys[i]][#body[keys[i]]+1]  = descr
					body[keys[i]][#body[keys[i]]+1]  = filename_underscore_hacked
				end
			end
			file:close()
		end
	end
end

handle:close()

for k,v in pairs(body) do
	print("\\section*{" .. k .. "}")
	n = 1
	while n <= #v do
		ejemplon = "\\paragraph{Ejercicio " ..  (n+1)/2 .. "}"
		print(ejemplon)
		print(v[n])
		print("Resuelto en el archivo {\\tt " .. v[n+1] .. "}")
		n = n + 2
	end
end

print("\\end{document}")
