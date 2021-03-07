import coremltools, sys, os

def pb2cml(pb):
  model = coremltools.convert(pb)
  model.save(pb.replace('.pb', '.mlmodel'))

if len(sys.argv) < 1:
    print("Usage: pb2cml.py <*.pb>")

for pb in sys.argv[1:]:
    #print("pb: " + pb)
    if os.path.exists(pb) == False:
        print("Error pb " + pb + " does not exist")
    pb2cml(pb)
