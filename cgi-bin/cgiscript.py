#!/usr/bin/python

import cgi
import cgitb; cgitb.enable(display=0, logdir="/tmp")

form = cgi.FieldStorage()
name = form.getvalue("name")
address = form.getvalue("address")
if not (form.has_key("name") and form.has_key("address")):
	print "<H1>Error</H1>"
	print "Please fill in the name and address fields."
	return

print ("Content-type:text/html\n")
print ("<html>")
print ("<head>")
print ("<title>First python CGI script</title>")
print ("</head>")
print ("<body>")
print ("<h2>Hello, %s you really live at: %s?</h2>", % (name, address))
print ("</body>")
print ("</html>")