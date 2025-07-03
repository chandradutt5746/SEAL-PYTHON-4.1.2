from seal import *
import time

def bfv_example():
    """ BFV Homomorphic Encryption Example (Beginner Friendly)

    This function demonstrates how to use the BFV scheme from Microsoft SEAL in Python.
    It explains every step in detail, so even someone new to cryptography can follow along.

    What is Homomorphic Encryption?
    -------------------------------
    Homomorphic encryption lets you do math on encrypted numbers, so you can get the right answer
    *without ever seeing the original numbers*. It's like doing math with a locked box!

    What is the BFV Scheme?
    -----------------------
    BFV is a type of homomorphic encryption that works well for integers. It's great for privacy-preserving
    computations, like adding or multiplying numbers without revealing them."""

    print('BFV example')
    print('-' * 70)

    """1. **Set Encryption Parameters**
       - `EncryptionParameters(SchemeType.BFV)`: Choose the BFV scheme.
       - `poly_modulus_degree`: This controls how much data you can encrypt at once and how secure it is.
         - Common values: 1024, 2048, 4096, 8192, 16384, 32768 (must be a power of two).
         - Bigger numbers = more security and more space, but slower.
       - `coeff_modulus`: This is a list of big prime numbers that control how much noise the ciphertext can handle.
         - Use `CoeffModulus.BFVDefault(poly_modulus_degree)` for safe defaults.
       - `plain_modulus`: This is the biggest number you can encrypt directly.
         - For BFV, use a prime number (e.g., 1032193). Bigger numbers let you store bigger integers."""
    parms = EncryptionParameters(SchemeType.BFV)
    poly_modulus_degree = 4096
    parms.set_poly_modulus_degree(poly_modulus_degree)
    parms.set_coeff_modulus(CoeffModulus.BFVDefault(poly_modulus_degree))
    parms.set_plain_modulus(1032193)

    """2. **Create a SEAL Context**
       - `SEALContext(parms)`: This checks your parameters and prepares everything for encryption.

    3. **Generate Keys**
       - `KeyGenerator(context)`: Makes all the keys you need.
       - `public_key`: Used to encrypt data (can be shared).
       - `secret_key`: Used to decrypt data (keep this secret!).
       - You can also generate `relin_keys` and `galois_keys` for advanced operations.

    4. **Create Helper Objects**
       - `Encryptor`: Turns plaintext into ciphertext using the public key.
       - `Evaluator`: Lets you do math on ciphertexts (add, multiply, etc.).
       - `Decryptor`: Turns ciphertext back into plaintext using the secret key.
       - `BatchEncoder`: Lets you pack lots of numbers into one ciphertext (like a suitcase for numbers)."""
    context = SEALContext(parms)
    keygen = KeyGenerator(context)
    public_key = keygen.create_public_key()
    secret_key = keygen.secret_key()
    encryptor = Encryptor(context, public_key)
    evaluator = Evaluator(context)
    decryptor = Decryptor(context, secret_key)
    encoder = BatchEncoder(context)


    """5. **Encode and Encrypt Data**
       - You can't encrypt numbers directly; you must encode them first.
       - `encoder.slot_count()`: How many numbers you can pack at once (depends on `poly_modulus_degree`).
       - Here, we put the number 123 in the first slot, and zeros everywhere else.
       - `encoder.encode(values, plain)`: Packs the numbers into a `Plaintext`.
       - `encryptor.encrypt(plain)`: Encrypts the plaintext into a `SerializableCiphertext`.

    6. **Convert SerializableCiphertext to Ciphertext**
       - Some SEAL operations need a `Ciphertext` object, not a `SerializableCiphertext`.
       - We save to a file and load it back as a `Ciphertext`."""
    value = 123
    slot_count = encoder.slot_count()
    values = [value] + [0] * (slot_count - 1)
    plain = Plaintext()
    encoder.encode(values, plain)
    cipher_serializable = encryptor.encrypt(plain)

    # Convert to Ciphertext for Evaluator
    cipher_serializable.save('tmp_bfv_cipher.bin')
    cipher = Ciphertext()
    cipher.load(context, 'tmp_bfv_cipher.bin')
    print('[DEBUG] Encrypted value:', value)
    
    """7. **Homomorphic Operation (Add)**
       - We encode another number (456) and add it to the encrypted number.
       - `evaluator.add_plain_inplace(cipher, plain2)`: Adds the plaintext to the ciphertext.

    8. **Decrypt and Decode**
       - `decryptor.decrypt(cipher, plain_result)`: Decrypts the result.
       - `encoder.decode_uint64(plain_result)`: Gets the numbers back as a Python list.
    """
    values2 = [456] + [0] * (slot_count - 1)
    plain2 = Plaintext()
    encoder.encode(values2, plain2)
    evaluator.add_plain_inplace(cipher, plain2)
    print('[DEBUG] Performed add_plain_inplace')

    plain_result = Plaintext()
    decryptor.decrypt(cipher, plain_result)
    result = encoder.decode_uint64(plain_result)
    decoded = result[0]

    """9. **Print the Result**
       - Shows the answer after all the encrypted math!

    Other Parameter Options:
    -----------------------
    - You can use different `SchemeType` values: `BFV`, `BGV`, `CKKS`.
    - Try different `poly_modulus_degree` values for more/less security.
    - For real numbers, use the `CKKS` scheme and `CKKSEncoder`.
    """
    print('[DEBUG] Decoded result:', decoded)
    print('-' * 70)


def bfv_batching_example():
    """BFV Batching Example (Beginner Friendly)

    This function demonstrates how to use batching with the BFV scheme in Microsoft SEAL.
    Batching lets you encrypt and process many numbers at once, making computations much faster!

    What is Batching?
    -----------------
    Batching is like packing lots of numbers into one suitcase (ciphertext), so you can carry and process them together.
    This is possible when using the BFV or BGV schemes with batching enabled.
    It allows you to perform operations on multiple numbers at once, which is much more efficient than doing them one by one.
    """

    print('BFV batching example')
    print('-' * 70)
    """1. **Set Encryption Parameters**
       - `EncryptionParameters(SchemeType.BFV)`: Choose the BFV scheme.
       - `poly_modulus_degree`: Controls security and how many numbers you can pack.
         - Common values: 1024, 2048, 4096, 8192, 16384, 32768 (must be a power of two).
         - Bigger numbers = more security and more slots, but slower.
       - `coeff_modulus`: A list of big prime numbers that control how much noise the ciphertext can handle.
         - Use `CoeffModulus.BFVDefault(poly_modulus_degree)` for safe defaults.
       - `plain_modulus`: The largest number you can encrypt directly.
         - For BFV, use a prime number (e.g., 1032193). Bigger numbers let you store bigger integers.
    """
    parms = EncryptionParameters(SchemeType.BFV)
    poly_modulus_degree = 4096 
    parms.set_poly_modulus_degree(poly_modulus_degree)
    parms.set_coeff_modulus(CoeffModulus.BFVDefault(poly_modulus_degree))
    parms.set_plain_modulus(1032193)

    """2. **Create a SEAL Context**
       - `SEALContext(parms)`: Checks your parameters and sets up the encryption environment.

    3. **Generate Keys**
       - `KeyGenerator(context)`: Makes all the keys you need.
       - `public_key`: Used to encrypt data (can be shared).
       - `secret_key`: Used to decrypt data (keep this secret!).

    4. **Create Helper Objects**
       - `Encryptor`: Encrypts plaintext using the public key.
       - `Evaluator`: Lets you do math on ciphertexts (add, multiply, etc.).
       - `Decryptor`: Decrypts ciphertext using the secret key.
       - `BatchEncoder`: Packs many numbers into one ciphertext.
    """
    print('Creating SEAL context and keys...')
    print('-' * 70)
    context = SEALContext(parms)
    keygen = KeyGenerator(context)
    public_key = keygen.create_public_key()
    secret_key = keygen.secret_key()
    print('[DEBUG] Generated public and secret keys')
    # Create Encryptor, Evaluator, Decryptor, and BatchEncoder
    print('Creating Encryptor, Evaluator, Decryptor, and BatchEncoder...')
    print('-' * 70)
    encryptor = Encryptor(context, public_key)
    evaluator = Evaluator(context)
    decryptor = Decryptor(context, secret_key)
    encoder = BatchEncoder(context)
    print('[DEBUG] Created Encryptor, Evaluator, Decryptor, and BatchEncoder')

    """5. **Batch Encode and Encrypt a Vector**
       - We create a list of numbers (e.g., [0, 1, 2, ..., 9]) and fill the rest with zeros.
       - `encoder.encode(values, plain)`: Packs the numbers into a `Plaintext`.
       - `encryptor.encrypt(plain)`: Encrypts the plaintext into a `SerializableCiphertext`.

    6. **Convert SerializableCiphertext to Ciphertext**
       - Some SEAL operations need a `Ciphertext` object, not a `SerializableCiphertext`.
       - We save to a file and load it back as a `Ciphertext`.
    """
    print('Batch encoding and encrypting a vector...')
    # Batch encode and encrypt a vector
    # We will encode a vector of numbers from 0 to 9 and fill the rest with zeros
    # The slot count is determined by the poly modulus degree
    # The values are encoded into a plaintext, which is then encrypted into a serializable ciphertext
    # Finally, we load the serializable ciphertext into a ciphertext object for evaluation
    print('-' * 70)
    print('Encoding vector [0, 1, 2, ..., 9] with zeros...')
    print('-' * 70)
    """7. **Homomorphic Operation (Add a Vector)**
       - We create another vector (e.g., [5, 5, ..., 5]) and add it to the encrypted vector.
       - `evaluator.add_plain_inplace(cipher, plain2)`: Adds the plaintext vector to the ciphertext.
    """
    values = [i for i in range(10)] + [0] * (encoder.slot_count() - 10)
    plain = Plaintext()
    encoder.encode(values, plain)
    cipher_serializable = encryptor.encrypt(plain)

    # Convert to Ciphertext for Evaluator
    cipher_serializable.save('tmp_bfv_batch_cipher.bin')
    cipher = Ciphertext()
    cipher.load(context, 'tmp_bfv_batch_cipher.bin')
    print('[DEBUG] Encrypted vector:', values[:10])

    # Add a constant vector
    print('Performing homomorphic operation (add vector)...')
    print('-' * 70)
    # Add a constant vector to the ciphertext
    # We will create a vector of 5s and add it to the encrypted vector
    # The vector is encoded into a plaintext, which is then added to the ciphertext
    # This is similar to the BFV example, but we will use batching to add a vector
    # The slot count is determined by the poly modulus degree
    add_vec = [5] * 10 + [0] * (encoder.slot_count() - 10)
    plain2 = Plaintext()
    encoder.encode(add_vec, plain2)
    evaluator.add_plain_inplace(cipher, plain2)
    print('[DEBUG] Performed add_plain_inplace with vector')

    # Decrypt and decode
    """8. **Decrypt and Decode**
       - `decryptor.decrypt(cipher, plain_result)`: Decrypts the result.
       - `encoder.decode_uint64(plain_result)`: Gets the numbers back as a Python list.

    9. **Print the Result**
       - Shows the answer after all the encrypted math!
    """
    print('Decrypting and decoding result...')
    print('-' * 70)
    plain_result = Plaintext()
    decryptor.decrypt(cipher, plain_result)
    result = encoder.decode_uint64(plain_result)
    print('[DEBUG] Decoded result:', result[:10])
    print('[DEBUG] Sum of result vector:', sum(result))
    print('-' * 70)


def bgv_example():
    """BGV Homomorphic Encryption Example (Beginner Friendly)

    This function demonstrates how to use the BGV scheme from Microsoft SEAL in Python.
    Every step is explained in simple terms, so even someone new to cryptography can follow along.

    What is the BGV Scheme?
    -----------------------
    BGV is another type of homomorphic encryption, similar to BFV, but with some differences in how it handles noise and batching.
    It's also used for privacy-preserving computations on integers.
    It allows you to perform operations on encrypted data, like multiplying or adding numbers, without ever seeing the original numbers."""

    print('BGV example')
    print('-' * 70)

    # Encryption Parameters
    """1. **Set Encryption Parameters**
       - `EncryptionParameters(SchemeType.BGV)`: Choose the BGV scheme.
       - `poly_modulus_degree`: Controls security and how much data you can encrypt at once.
         - Must be a power of two (e.g., 1024, 2048, 4096, 8192, 16384, 32768).
         - Higher values mean more security and more slots, but slower computation.
       - `coeff_modulus`: A list of big prime numbers that control how much noise the ciphertext can handle.
         - Use `CoeffModulus.BFVDefault(poly_modulus_degree)` for safe defaults.
       - `plain_modulus`: The largest number you can encrypt directly.
         - For BGV, use a prime number (e.g., 1032193).
    """
    parms = EncryptionParameters(SchemeType.BGV)
    poly_modulus_degree = 4096
    parms.set_poly_modulus_degree(poly_modulus_degree)
    parms.set_coeff_modulus(CoeffModulus.BFVDefault(poly_modulus_degree))
    parms.set_plain_modulus(1032193)

    """2. **Create a SEAL Context**
       - `SEALContext(parms)`: Checks your parameters and sets up the encryption environment.

    3. **Generate Keys**
       - `KeyGenerator(context)`: Makes all the keys you need.
       - `public_key`: Used to encrypt data (can be shared).
       - `secret_key`: Used to decrypt data (keep this secret!).

    4. **Create Helper Objects**
       - `Encryptor`: Encrypts plaintext using the public key.
       - `Evaluator`: Lets you do math on ciphertexts (add, multiply, etc.).
       - `Decryptor`: Decrypts ciphertext using the secret key.
       - `BatchEncoder`: Packs many numbers into one ciphertext (like a suitcase for numbers).
    """
    print('Creating SEAL context and keys...')
    print('-' * 70)
    # Create SEAL context and keys
    # This is similar to the BFV example, but using BGV scheme
    # The parameters are the same, but we use SchemeType.BGV instead of SchemeType.BFV
    # The rest of the code is similar, but we will use BGV-specific operations
    
    context = SEALContext(parms)
    keygen = KeyGenerator(context)
    public_key = keygen.create_public_key()
    secret_key = keygen.secret_key()
    print('[DEBUG] Generated public and secret keys')
    # Create Encryptor, Evaluator, Decryptor, and BatchEncoder
    print('Creating Encryptor, Evaluator, Decryptor, and BatchEncoder...')
    print('-' * 70)
    # These objects are used for encryption, evaluation, decryption, and encoding/decoding
    # Encryptor is used to encrypt plaintext into ciphertext
    # Evaluator is used to perform operations on ciphertexts
    # Decryptor is used to decrypt ciphertext back into plaintext
    # BatchEncoder is used to encode and decode vectors of numbers
    encryptor = Encryptor(context, public_key)
    evaluator = Evaluator(context)
    decryptor = Decryptor(context, secret_key)
    encoder = BatchEncoder(context)

    """5. **Encode and Encrypt Data**
       - You can't encrypt numbers directly; you must encode them first.
       - `encoder.slot_count()`: How many numbers you can pack at once (depends on `poly_modulus_degree`).
       - Here, we put the number 321 in the first slot, and zeros everywhere else.
       - `encoder.encode(values, plain)`: Packs the numbers into a `Plaintext`.
       - `encryptor.encrypt(plain)`: Encrypts the plaintext into a `SerializableCiphertext`.

    6. **Convert SerializableCiphertext to Ciphertext**
       - Some SEAL operations need a `Ciphertext` object, not a `SerializableCiphertext`.
       - We save to a file and load it back as a `Ciphertext`.
    """
    print('Encoding and encrypting data...')
    print('-' * 70)
    # Encode and encrypt a single value
    # Similar to the BFV example, but using BGV scheme
    # We will encode the value 321 and encrypt it
    # The slot count is determined by the poly modulus degree
    # The value is encoded into a plaintext, which is then encrypted into a serializable ciphertext
    # Finally, we load the serializable ciphertext into a ciphertext object for evaluation
    # This is similar to the BFV example, but we will use BGV-specific operations
    print('Encoding value 321...')
    print('-' * 70)
    value = 321
    slot_count = encoder.slot_count()
    values = [value] + [0] * (slot_count - 1)
    # Create a vector with the value in the first slot and zeros elsewhere
    plain = Plaintext()
    encoder.encode(values, plain)
    
    cipher_serializable = encryptor.encrypt(plain)

    # Convert to Ciphertext for Evaluator
    cipher_serializable.save('tmp_bgv_cipher.bin')
    cipher = Ciphertext()
    cipher.load(context, 'tmp_bgv_cipher.bin')
    print('[DEBUG] Encrypted value:', value)

    # Multiply by a constant
    """7. **Homomorphic Operation (Multiply)**
       - We encode another number (2) and multiply it with the encrypted number.
       - `evaluator.multiply_plain_inplace(cipher, plain2)`: Multiplies the ciphertext by the plaintext.
    """
    print('Performing homomorphic operation (multiply)...')
    print('-' * 70)
    # Multiply the ciphertext by a constant
    values2 = [2] + [0] * (slot_count - 1)
    plain2 = Plaintext()
    encoder.encode(values2, plain2)
    evaluator.multiply_plain_inplace(cipher, plain2)
    print('[DEBUG] Performed multiply_plain_inplace')

    """8. **Decrypt and Decode**
       - `decryptor.decrypt(cipher, plain_result)`: Decrypts the result.
       - `encoder.decode_uint64(plain_result)`: Gets the numbers back as a Python list.

    9. **Print the Result**
       - Shows the answer after all the encrypted math!
    
    For more, see: (https://github.com/microsoft/SEAL) Official Microsoft SEAL documentation.
    """
    # Decrypt and decode
    plain_result = Plaintext()
    decryptor.decrypt(cipher, plain_result)
    print('Decrypting and decoding result...')
    result = encoder.decode_uint64(plain_result)
    decoded = result[0]
    print('[DEBUG] Decoded result:', decoded)
    print('-' * 70)

    
if __name__ == "__main__":
    bfv_example()
    bfv_batching_example()
    bgv_example()
    print('All bssic examples completed successfully.')