import wx

# in order to run this you need to make sure that you have Python and wxPython both installed.
# they must both be either 32 bit or 64 bit, but they must both be the same

# create a new app, don't redirect dtdout/stderr to a window
app = wx.App(False)

# a frame is a top level window
frame = wx.Frame(None, wx.ID_ANY, "Hello World!!!")

# show the frame
frame.Show(True)

app.MainLoop()