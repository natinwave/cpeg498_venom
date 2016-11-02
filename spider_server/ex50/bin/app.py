import web
from web import form
import json

render = web.template.render('templates/')

urls = (
	'/', 'index',
	'/info', 'info'
)
app = web.application(urls, globals())

action_form = form.Form(
    form.Textbox("action"))

class index: 
    def GET(self): 
        form = action_form()
        # make sure you create a copy of the form by calling it (line above)
        # Otherwise changes will appear globally
        return render.index(form)

    def POST(self): 
        form = action_form() 
        if not form.validates(): 
            return render.index(form)
        else:
        	#TODO: Write to a JSON file here.
        	#NOTE: The Raspberry Pi will be connected to WiFi and will
        	#      periodically request the JSON file from this web server.
        	action = form["action"].value
        	print "action: " + action
        	latest_info = {"action": action}
        	with open('info.json', 'w') as info_json_file:
        		json.dump(latest_info, info_json_file)
        	raise web.seeother('/') #redirect to the index page
        	
class info:
	def GET(self):
		latest_info = {}
		with open('info.json') as info_json_file:
			latest_info = json.load(info_json_file)
		return str(latest_info)

if __name__=="__main__":
    web.internalerror = web.debugerror
    app.run()