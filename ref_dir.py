from pymoo.util.ref_dirs import get_reference_directions
import numpy as np

ref_dirs = get_reference_directions("das-dennis", 3, n_partitions=12)

print(ref_dirs)
np.savetxt("ref_dirs.txt", ref_dirs);
