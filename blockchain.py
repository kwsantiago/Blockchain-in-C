from block import Block

blockchain = [Block.create_genesis_block()]

print("The Genesis Block has been created!")
print("Hash: %s" % blockchain[-1].hash)

