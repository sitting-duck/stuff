import wx
import os

# in order to run this you need to make sure that you have Python and wxPython both installed.
# they must both be either 32 bit or 64 bit, but they must both be the same

class MainWindow(wx.Frame): # it should be noted that in wxPython Frame actually means Window in the typical sense, don't get it confused
	"""We simply derive a new class of Frame"""
	def __init__(self, parent, title):
		wx.Frame.__init__(self, parent, title=title, size=(500, 500))
		
		self.tabController = wx.Notebook(self, style=wx.NB_TOP)			# create the tabcontroller and place the tabs at the top
		
		# self.tabController.control = wx.TextCtrl(self.tabController, style=wx.TE_MULTILINE)		# set the tabController as a text_cntrl
		self.CreateStatusBar() 										# a status bar in the bottom of the window
		
		#setting up the menu
		filemenu = wx.Menu()
		
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		#												MAKE THE MENU ITEMS
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		# wx.ID_ABOUT and wx.ID_EXIT are standard IDs provided by wxWidgets
		#  It is a good habit to use the standard ID if there is one available. This helps wxWidgets know how to display the widget in
		# each platform to make it look more native.
		
		menuOpen = filemenu.Append(wx.ID_OPEN,   # the widget id
		"Open",									# the name of the menu option
		"Open a file to edit")					# the caption that will show in that status bar at the bottom of the window
		
		filemenu.AppendSeparator()
		
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
		
		# use bind to bind onOpen function to "Open" menu item
		self.Bind(wx.EVT_MENU,					# the code for the "select menu item" event
		self.onOpen,							# the method that will be executed when the menu item is selected
		menuOpen)								# the "Open" menu item we are binding to the main window
		
		# use bind to bind OnAbout function to "About" menu item
		self.Bind(wx.EVT_MENU,					# the code for the "select menu item" event
		self.OnAbout,							# the method that will be executed when the menu item is selected
		menuAbout)								# the "About" menu item we are binding to the main window
		
		# use bind to bind OnExit function to "Exit" menu item
		self.Bind(wx.EVT_MENU,					# the code for the "select menu item" event
		self.OnExit, 							# the method that will be executed when the menu item is selected
		menuExit)								# the "Exit" menu item we are binding to the main window
		
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		#											ATTACH THE MENU TO THE WINDOW
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		
		menuBar = wx.MenuBar()					# creating the menu bar
		menuBar.Append(filemenu, "File") 		# adding the file menu we just made to the menu bar and naming it "File"
		self.SetMenuBar(menuBar)		 		# adding the MenuBar to the Frame content
		self.Show(True)
		
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
		#													MENU CALLBACKS
		# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #	
	def onOpen(self, event):
		"""Open a file"""
		self.dirname = ''
		dialog = wx.FileDialog(self, "Choose a file", self.dirname, "", "*.*", wx.OPEN)
		if dialog.ShowModal() == wx.ID_OK:  # if a file was chosen successfully, instead of hitting cancel for example
											# "Modal" means that the user cannot do anything on the application until he clicks OK or Cancel.
			self.filename = dialog.GetFilename()								# get the filename from the dialog
			self.dirname = dialog.GetDirectory()								# get the name of the folder from the dialog
			file = open(os.path.join(self.dirname, self.filename), 'r')			# open the file
			textFromFileJustOpened = file.read()								# read the text from the file									 
			
			text_ctrl = wx.TextCtrl(self.tabController, style=wx.TE_MULTILINE)	# create the notebook page as a wx.TextCtrl
			text_ctrl.SetValue(textFromFileJustOpened)							# set its' content to be the text from the file we just opened
			
			self.tabController.AddPage(text_ctrl, self.filename, select=True)	# add the file just opened as a new tab
			
			file.close()
			
		dialog.Destroy()
	
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