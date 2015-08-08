import wx

# in order to run this you need to make sure that you have Python and wxPython both installed.
# they must both be either 32 bit or 64 bit, but they must both be the same

class MainWindow(wx.Frame): # it should be noted that in wxPython Frame actually means Window in the typical sense, don't get it confused
	"""We simply derive a new class of Frame"""
	def __init__(self, parent, title):
		wx.Frame.__init__(self, parent, title=title, size=(200, 100))
		self.control = wx.TextCtrl(self, style=wx.TE_MULTILINE)
		self.CreateStatusBar() # a status bar in the bottom of the window
		
		#setting up the menu
		filemenu = wx.Menu()
		
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		#												MAKE THE MENU ITEMS
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		# wx.ID_ABOUT and wx.ID_EXIT are standard IDs provided by wxWidgets
		#  It is a good habit to use the standard ID if there is one available. This helps wxWidgets know how to display the widget in
		# each platform to make it look more native.
		
		menuAbout = filemenu.Append(wx.ID_ABOUT,# the widget id
		"About", 								# the name of the menu option
		" Information about this program")		# the caption that will show in the status bar at the bottom of the window
		
		filemenu.AppendSeparator()
		
		menuExit = filemenu.Append(wx.ID_EXIT,	# the widget id
		"Exit",									# the name of the menu option
		"Terminate the program")				# the caption that will show in that status bar at the bottom of the window
		
		
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		#												BIND THE MENU ITEMS
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		# use bind to bind OnAbout function to "About" menu item
		self.Bind(wx.EVT_MENU,					# the code for the "select menu item" event
		self.OnAbout,							# the method that will be executed when the menu item is selected
		menuAbout)								# the "About" menu item we are binding to the main window
		
		# use bind to bind OnExit function to "Exit" menu item
		self.Bind(wx.EVT_MENU,					# the code for the "select menu item" event
		self.OnExit, 							# the method that will be executed when the menu item is selected
		menuExit)								# the "Exit" menu item we are binding to the main window
		
		
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		#												ATTACH THE MENU TO THE WINDOW
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		#Creating the menu bar
		menuBar = wx.MenuBar()
		menuBar.Append(filemenu, "File") 		# adding the file menu we just made to the menu bar and naming it "File"
		self.SetMenuBar(menuBar)		 		# adding the MenuBar to the Frame content
		self.Show(True)
		
		
	def OnAbout(self, event):
		"""When the user selects "About" from the file menu a message dialog box pops up with a description about the program, and an OK button"""
		dialog = wx.MessageDialog(self,
		"dat text editor tho", 					# the text inside the dialog
		"about dat text editor tho",			# the title of the dialog window
		wx.OK)									# dat ok button tho
		
		dialog.ShowModal()						# shows the dialog
		dialog.Destroy()						# destroy the dialog when finished
		
	def OnExit(self, event):
		"""When the user selects "Exit" from the file menu, this function is called and the program exits"""
		self.Close(True)						# Close the Frame
		
		
app = wx.App(False)
frame = MainWindow(None, 'that editor tho')
app.MainLoop()