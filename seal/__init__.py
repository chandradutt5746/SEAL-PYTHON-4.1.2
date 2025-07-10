from .seal import *

# Security warning
SECURITY_WARNING = """
!!! SECURITY WARNING !!!
Handle cryptographic keys with extreme care.
Never log or transmit secret keys in plain text.
"""

print(f"SEAL Python Bindings {__version__} loaded")
print(SECURITY_WARNING)